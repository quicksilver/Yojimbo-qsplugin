//
//  QSYojimboPlugInAction.m
//  QSYojimboPlugIn
//
//  Created by Nicholas Jitkoff on 5/14/06.
//  Copyright __MyCompanyName__ 2006. All rights reserved.
//

#import "QSYojimboPlugInAction.h"
#import "QSYojimboPlugInDefines.h"
#import "Yojimbo.h"

@implementation QSYojimboPlugInAction

#define kQSYojimboPlugInAction @"QSYojimboPlugInAction"

- (id)init
{
    self = [super init];
    if (self) {
        Yojimbo = [[SBApplication applicationWithBundleIdentifier:@"com.barebones.yojimbo"] retain];
    }
    return self;
}

- (void)dealloc
{
    [Yojimbo release];
    [super dealloc];
}

# pragma mark - Quicksilver Actions

- (QSObject *)addObject:(QSObject *)dObject withName:(QSObject *)itemName
{
	NSString *uuid = nil;
    // figure out how to add this thing based on type
    if ([dObject containsType:QSURLType])
    {
        // add this as a "bookmark"
        YojimboBookmarkItem *bookmark = [[[Yojimbo classForScriptingClass:@"bookmark item"] alloc] init];
        [[Yojimbo databaseItems] addObject:bookmark];
        [bookmark setName:[itemName stringValue]];
        [bookmark setLocation:[dObject objectForType:QSURLType]];
        uuid = [bookmark id];
    } else if ([dObject containsType:QSFilePathType]) {
        // import a file
        id importedItem = [Yojimbo import:[dObject objectForType:QSFilePathType]];
        [(YojimboDatabaseItem *)importedItem setName:[itemName stringValue]];
        uuid = [(YojimboDatabaseItem *)importedItem id];
    } else {
        // add this as a "note"
        YojimboNoteItem *note = [[[Yojimbo classForScriptingClass:@"note item"] alloc] init];
        [[Yojimbo databaseItems] addObject:note];
        [note setName:[itemName stringValue]];
        [note setContents:[dObject stringValue]];
        uuid = [note id];
    }
    QSObject *newObject=[QSObject makeObjectWithIdentifier:uuid];
    [newObject setName:[itemName stringValue]];
    [newObject setDetails:@"New Yojimbo Item"];
    [newObject setIdentifier:uuid];
    [newObject setObject:uuid forType:kQSYojimboPlugInType];
    [newObject setPrimaryType:kQSYojimboPlugInType];
    return newObject;
}

- (QSObject *)addTagsToItem:(QSObject *)dObject withTags:(QSObject *)tags
{
    // get a list of tags passed in
    NSArray *tagNames = [tags arrayForType:kQSYojimboTagType];
    // add the tags to the item(s)
    YojimboDatabaseItem *yojimboItem = nil;
    for (NSString *uuid in [dObject arrayForType:kQSYojimboPlugInType])
    {
        yojimboItem = [self yojimboItemWithUUID:uuid];
        [Yojimbo addTags:tagNames to:yojimboItem];
    }
    return nil;
}

- (QSObject *)appendToNote:(QSObject *)dObject content:(QSObject *)iObject
{
    NSString *uuid = [dObject identifier];
    NSString *text = [iObject stringValue];
    YojimboNoteItem *note = [self yojimboItemWithUUID:uuid];
    [Yojimbo append:text to:note];
    return nil;
}

- (QSObject *)addObjectArchive:(QSObject *)dObject
{
    NSString *urlString = [dObject objectForType:QSURLType];
    NSString *addUrlArchive = [NSString stringWithFormat:@"on add_url_archive(theURL)\rtell application \"Yojimbo\" to return id of (make new web archive item with contents theURL)\rend add_url_archive"];
    NSAppleScript *script = [[NSAppleScript alloc] initWithSource:addUrlArchive];
    NSString *uuid = [[script executeSubroutine:@"add_url_archive" arguments:[NSArray arrayWithObject:urlString] error:nil] stringValue];
    QSObject *newObject = [QSObject makeObjectWithIdentifier:uuid];
    [newObject setName:[dObject name]];
    [newObject setObject:uuid forType:kQSYojimboPlugInType];
    [newObject setPrimaryType:kQSYojimboPlugInType];
    [newObject setDetails:urlString];
    return newObject;
}

- (QSObject *)showObject:(QSObject *)dObject
{
    NSString *uuid = [dObject objectForType:kQSYojimboPlugInType];
    [Yojimbo reveal:[self yojimboItemWithUUID:uuid]];
    return nil;
}

# pragma mark - Quicksilver Validation

- (NSArray *) validActionsForDirectObject:(QSObject *)dObject indirectObject:(QSObject *)iObject{
    // the list of actions to return
    NSMutableArray *actions = [NSMutableArray arrayWithCapacity:1];
    // check based on item type
    if ([dObject containsType:kQSYojimboPlugInType])
    {
        [actions addObject:@"QSYojimboShowAction"];
        [actions addObject:@"QSYojimboTagAction"];
        // only allow appending to notes
        if ([[dObject objectForMeta:@"itemKind"] isEqualToString:@"com.barebones.yojimbo.yojimbonote"])
        {
            [actions addObject:@"QSYojimboAppendAction"];
        }
    } else {
        [actions addObject:@"QSYojimboAddAction"];
        [actions addObject:@"QSYojimboNameAddAction"];
    }
    return actions;
}

- (NSArray *)validIndirectObjectsForAction:(NSString *)action directObject:(QSObject *)dObject{
    if ([action isEqualToString:@"QSYojimboAddAction"] || [action isEqualToString:@"QSYojimboNameAddAction"])
    {
        return [NSArray arrayWithObject: [QSObject textProxyObjectWithDefaultValue:[dObject name]]];
    }
    if ([action isEqualToString:@"QSYojimboAppendAction"])
    {
        NSString *clipBoardContents=[[NSPasteboard pasteboardWithName:NSGeneralPboard] stringForType:NSStringPboardType];
        return [NSArray arrayWithObject: [QSObject textProxyObjectWithDefaultValue:clipBoardContents]];
    }
    if ([action isEqualToString:@"QSYojimboTagAction"])
    {
        // return a list of tags
        return [QSLib scoredArrayForString:nil inSet:[QSLib arrayForType:kQSYojimboTagType]];
    }
    // no matches - return empty string
    QSObject *textObject=[QSObject textProxyObjectWithDefaultValue:@""];
    return [NSArray arrayWithObject:textObject];
}

# pragma mark - Helpers

- (id)yojimboItemWithUUID:(NSString *)uuid
{
    // use UUID to locate and return a Scripting Bridge object
    return [[Yojimbo databaseItems] objectWithID:uuid];
}

@end

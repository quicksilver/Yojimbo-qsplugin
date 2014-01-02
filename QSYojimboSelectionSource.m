//
//  QSYojimboSelectionSource.m
//  QSYojimboPlugIn
//
//  Created by Rob McBroom on 2013/12/31.
//
//

#import "QSYojimboSelectionSource.h"
#import "QSYojimboPlugInDefines.h"
#import "Yojimbo.h"

@implementation QSYojimboSelectionSource

- (id)resolveProxyObject:(id)proxy
{
    YojimboApplication *Yojimbo = [SBApplication applicationWithBundleIdentifier:@"com.barebones.yojimbo4"];
    NSArray *ysel = [Yojimbo selection];
    if (ysel) {
        NSMutableArray *selectionObjects = [NSMutableArray array];
        QSObject *object = nil;
        for (YojimboDatabaseItem *item in ysel) {
            // get ID and use that to pull from catalog
            object = [QSObject objectWithIdentifier:[item id]];
            if (object) {
                [selectionObjects addObject:object];
            }
        }
        if ([selectionObjects count]) {
            return [QSObject objectByMergingObjects:selectionObjects];
        }
    }
    return nil;
}

@end

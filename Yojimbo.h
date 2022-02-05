/*
 * Yojimbo.h
 */

#import <AppKit/AppKit.h>
#import <ScriptingBridge/ScriptingBridge.h>


@class YojimboApplication, YojimboWindow, YojimboBrowserWindow, YojimboEditorWindow, YojimboQuickInputPanelObject, YojimboLabel, YojimboTag, YojimboCollection, YojimboFolderCollection, YojimboTagCollection, YojimboSmartCollection, YojimboBuiltinSmartCollection, YojimboLibraryCollection, YojimboTrashCollection, YojimboDatabaseItem, YojimboBookmarkItem, YojimboImageItem, YojimboNoteItem, YojimboPasswordItem, YojimboPdfArchiveItem, YojimboSerialNumberItem, YojimboWebArchiveItem;

enum YojimboSaveOptions {
	YojimboSaveOptionsYes = 'yes ' /* Save the file. */,
	YojimboSaveOptionsNo = 'no  ' /* Do not save the file. */,
	YojimboSaveOptionsAsk = 'ask ' /* Ask the user whether or not to save the file. */
};
typedef enum YojimboSaveOptions YojimboSaveOptions;

enum YojimboTagCollectionBehavior {
	YojimboTagCollectionBehaviorMatchItemsWithAllTags = 'TgAl' /* match items which have all of the tags associated with the tag collection */,
	YojimboTagCollectionBehaviorMatchItemsWithAnyTag = 'TgAn' /* match items which have any of the tags associated with the tag collection */
};
typedef enum YojimboTagCollectionBehavior YojimboTagCollectionBehavior;

@protocol YojimboGenericMethods

- (void) open;  // Open a document.
- (void) closeSaving:(YojimboSaveOptions)saving;  // Close a document.
- (BOOL) exists;  // Verify if an object exists.
- (void) delete;  // Delete an object.
- (id) moveTo:(id)to;  // Move object(s) to a new location.

@end



/*
 * Standard Suite
 */

// The application's top-level scripting object.
@interface YojimboApplication : SBApplication

- (SBElementArray<YojimboWindow *> *) windows;

@property (copy, readonly) NSString *name;  // The name of the application.
@property (readonly) BOOL frontmost;  // Is this the frontmost (active) application?
@property (copy, readonly) NSString *version;  // The version of the application.

- (void) open:(id)x;  // Open a document.
- (void) quit;  // Quit the application.
- (id) import:(id)x;  // Import the file(s) into Yojimbo.
- (id) export:(NSArray<YojimboDatabaseItem *> *)x to:(NSURL *)to;  // Export the specified item(s).
- (void) emptyTrash;  // Empty the trash.
- (void) reveal:(id)x;  // Reveal a database item or collection.
- (void) add:(NSArray<SBObject *> *)x to:(SBObject *)to;  // Add objects(s) to a container.
- (void) remove:(NSArray<SBObject *> *)x from:(SBObject *)from;  // Remove object(s) from a container.
- (void) addTags:(id)x to:(id)to;  // Add tag(s) to a database item or tag collection.
- (void) removeTags:(id)x from:(id)from;  // Remove tag(s) from a database item or tag collection.
- (void) append:(NSString *)x to:(YojimboNoteItem *)to;  // Append text to the contents of a note.
- (void) prepend:(NSString *)x to:(YojimboNoteItem *)to;  // Prepend text to the contents of a note.

@end

// A window.
@interface YojimboWindow : SBObject <YojimboGenericMethods>

@property (copy) NSString *name;  // The title of the window.
- (NSInteger) id;  // The unique identifier of the window.
@property NSRect bounds;  // The bounding rectangle of the window.
@property (readonly) BOOL closeable;  // Can the window be closed?
@property NSInteger index;  // The index of the window in the back-to-front window ordering.
@property (readonly) BOOL minimizable;  // Can the window be minimized?
@property BOOL minimized;  // Is this window currently minimized?
@property (readonly) BOOL resizable;  // Can the window be resized?
@property BOOL visible;  // Is the window visible?
@property (readonly) BOOL zoomable;  // Can the window be zoomed?
@property BOOL zoomed;  // Is the window zoomed?


@end



/*
 * Yojimbo Suite
 */

@interface YojimboApplication (YojimboSuite)

- (SBElementArray<YojimboBrowserWindow *> *) browserWindows;
- (SBElementArray<YojimboEditorWindow *> *) editorWindows;
- (SBElementArray<YojimboLabel *> *) labels;
- (SBElementArray<YojimboTag *> *) tags;
- (SBElementArray<YojimboCollection *> *) collections;
- (SBElementArray<YojimboFolderCollection *> *) folderCollections;
- (SBElementArray<YojimboTagCollection *> *) tagCollections;
- (SBElementArray<YojimboBuiltinSmartCollection *> *) builtinSmartCollections;
- (SBElementArray<YojimboDatabaseItem *> *) databaseItems;
- (SBElementArray<YojimboBookmarkItem *> *) bookmarkItems;
- (SBElementArray<YojimboImageItem *> *) imageItems;
- (SBElementArray<YojimboNoteItem *> *) noteItems;
- (SBElementArray<YojimboPasswordItem *> *) passwordItems;
- (SBElementArray<YojimboPdfArchiveItem *> *) pdfArchiveItems;
- (SBElementArray<YojimboSerialNumberItem *> *) serialNumberItems;
- (SBElementArray<YojimboWebArchiveItem *> *) webArchiveItems;

@property (copy, readonly) NSArray<SBObject *> *selection;  // The selection in the frontmost window.
@property (copy, readonly) YojimboLibraryCollection *library;  // The library collection.
@property (copy, readonly) YojimboTrashCollection *trash;  // The trash collection.
@property (copy, readonly) YojimboQuickInputPanelObject *quickInputPanel;  // The quick input panel.

@end

// The main Yojimbo window.
@interface YojimboBrowserWindow : YojimboWindow

@property (copy, readonly) NSArray<SBObject *> *selection;  // The currently selected objects.
@property (copy, readonly) NSArray<YojimboCollection *> *selectedCollections;  // The selected collections.
@property (copy, readonly) NSArray<YojimboDatabaseItem *> *selectedItems;  // The selected items.


@end

// An editor window.
@interface YojimboEditorWindow : YojimboWindow

@property (copy, readonly) YojimboDatabaseItem *databaseItem;  // The database item associated with this editor window.


@end

// The class of the quick input panel.
@interface YojimboQuickInputPanelObject : SBObject <YojimboGenericMethods>

@property BOOL visible;  // Is the quick input panel visible?


@end

// A label.
@interface YojimboLabel : SBObject <YojimboGenericMethods>

@property (copy) NSString *name;  // The label's name.
- (NSString *) id;  // The unique identifier of the label.
@property (copy) NSColor *color;  // The label's color.


@end

// A tag.
@interface YojimboTag : SBObject <YojimboGenericMethods>

@property (copy) NSString *name;  // The tag's name.
- (NSString *) id;  // The unique identifier of the tag.


@end

// The abstract base class of all Yojimbo collections.
@interface YojimboCollection : SBObject <YojimboGenericMethods>

- (SBElementArray<YojimboDatabaseItem *> *) databaseItems;
- (SBElementArray<YojimboBookmarkItem *> *) bookmarkItems;
- (SBElementArray<YojimboImageItem *> *) imageItems;
- (SBElementArray<YojimboNoteItem *> *) noteItems;
- (SBElementArray<YojimboPasswordItem *> *) passwordItems;
- (SBElementArray<YojimboPdfArchiveItem *> *) pdfArchiveItems;
- (SBElementArray<YojimboSerialNumberItem *> *) serialNumberItems;
- (SBElementArray<YojimboWebArchiveItem *> *) webArchiveItems;

@property (copy) NSString *name;  // The collection's name.
- (NSString *) id;  // The unique identifier of the collection.
@property (copy) NSString *comments;  // The collection's comments.
@property (copy) NSImage *icon;  // The collection's icon.
@property BOOL showInDropDock;  // Determines whether or not this collection appears in the Drop Dock.


@end

// A folder collection.
@interface YojimboFolderCollection : YojimboCollection


@end

// A tag collection.
@interface YojimboTagCollection : YojimboCollection

- (SBElementArray<YojimboTag *> *) tags;

@property YojimboTagCollectionBehavior tagCollectionBehavior;  // The behavior used by the tag collection to match items.


@end

// A smart collection.
@interface YojimboSmartCollection : YojimboCollection


@end

// A builtin smart collection.
@interface YojimboBuiltinSmartCollection : YojimboSmartCollection


@end

// The library contains all the items you have stored in Yojimbo.
@interface YojimboLibraryCollection : YojimboBuiltinSmartCollection


@end

// The trash contains all the items pending permanent removal.
@interface YojimboTrashCollection : YojimboBuiltinSmartCollection


@end

// The abstract base class of all Yojimbo database items.
@interface YojimboDatabaseItem : SBObject <YojimboGenericMethods>

- (SBElementArray<YojimboTag *> *) tags;

@property (copy) NSString *name;  // The item's name.
- (NSString *) id;  // The unique identifier of the item.
@property (copy) NSString *comments;  // The item's comments.
@property (copy, readonly) NSDate *creationDate;  // The date on which the item was created
@property (copy, readonly) NSDate *modificationDate;  // The date on which the item was last modified.
@property (copy, readonly) NSDate *dateImported;  // The date on which the item was imported into Yojimbo.
@property BOOL flagged;  // Is the item flagged?
@property (copy) id label;  // The item's label.
@property (copy) id labelName;  // The name of the item's label.


@end

// A bookmark item.
@interface YojimboBookmarkItem : YojimboDatabaseItem

@property (copy) NSString *location;  // The location/URL of the bookmark.
@property BOOL moveToTrashAfterOpening;  // Move the item to the trash after opening it?
@property (copy, readonly) NSDate *lastOpenedDate;  // The date on which the item was last opened.


@end

// An image item.
@interface YojimboImageItem : YojimboDatabaseItem

@property (readonly) BOOL encrypted;  // Is the image encrypted?

- (void) encrypt;  // Encrypt an item.
- (void) decrypt;  // Decrypt an item.

@end

// A note item.
@interface YojimboNoteItem : YojimboDatabaseItem

@property (readonly) BOOL encrypted;  // Is the note encrypted?
@property (copy) NSString *contents;  // The contents of the note.

- (void) encrypt;  // Encrypt an item.
- (void) decrypt;  // Decrypt an item.

@end

// A password item.
@interface YojimboPasswordItem : YojimboDatabaseItem

@property (copy) NSString *location;  // The location/URL of the item.
@property (copy) NSString *account;  // The account of the item.
@property (copy) NSString *password;  // The password of the item.


@end

// A pdf archive item.
@interface YojimboPdfArchiveItem : YojimboDatabaseItem

@property (readonly) BOOL encrypted;  // Is the pdf archive encrypted?

- (void) encrypt;  // Encrypt an item.
- (void) decrypt;  // Decrypt an item.

@end

// A serial number item.
@interface YojimboSerialNumberItem : YojimboDatabaseItem

@property (copy) NSString *ownerName;  // The product owner's name.
@property (copy) NSString *emailAddress;  // The product owner's email address.
@property (copy) NSString *organization;  // The product owner's organization.
@property (copy) NSString *serialNumber;  // The product serial number.


@end

// A web archive item.
@interface YojimboWebArchiveItem : YojimboDatabaseItem

@property (readonly) BOOL encrypted;  // Is the web archive encrypted?
@property (copy, readonly) NSString *sourceURL;  // The source URL for the web archive data.

- (void) encrypt;  // Encrypt an item.
- (void) decrypt;  // Decrypt an item.

@end


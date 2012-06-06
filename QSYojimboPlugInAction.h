//
//  QSYojimboPlugInAction.h
//  QSYojimboPlugIn
//
//  Created by Nicholas Jitkoff on 5/14/06.
//  Copyright __MyCompanyName__ 2006. All rights reserved.
//

#import <QSCore/QSObject.h>
#import <QSCore/QSActionProvider.h>
@class YojimboApplication;

@interface QSYojimboPlugInAction : QSActionProvider
{
    YojimboApplication *Yojimbo;
}
@end


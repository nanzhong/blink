////////////////////////////////////////////////////////////////////////////////
//
// B L I N K
//
// Copyright (C) 2016-2019 Blink Mobile Shell Project
//
// This file is part of Blink.
//
// Blink is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Blink is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Blink. If not, see <http://www.gnu.org/licenses/>.
//
// In addition, Blink is also subject to certain additional terms under
// GNU GPL version 3 section 7.
//
// You should have received a copy of these additional terms immediately
// following the terms and conditions of the GNU General Public License
// which accompanied the Blink Source Code. If not, see
// <http://www.github.com/blinksh/blink>.
//
////////////////////////////////////////////////////////////////////////////////

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@class TermDevice;
@class UndoManager;

@interface CC : NSObject

+ (void)initialize;
+ (NSString *)CTRL:(NSString *)c;
+ (NSString *)ESC:(NSString *)c;
+ (NSString *)KEY:(NSString *)c;

@end


@protocol UndoManagerDelegate
- (void)undoWithManager:(UndoManager *)manager;
- (void)redoWithManager:(UndoManager *)manager;
@end

@interface UndoManager: NSUndoManager
@property (weak) id<UndoManagerDelegate> undoManagerDelegate;

- (void)skipNext;

@end

@interface TermInput : UITextView

@property BOOL softwareKB;
@property BOOL capsLockPressed;
@property BOOL ctrlPressed;

@property (weak) TermDevice *device;

- (void)deviceWrite:(NSString *)input;
- (void)copyLink:(id)sender;
- (void)openLink:(id)sender;
- (void)yank:(id)sender;
- (void)pasteSelection:(id)sender;
- (void)fkeySeq:(UIKeyCommand *)cmd;
- (void)arrowSeq:(UIKeyCommand *)cmd;
- (void)cursorSeq:(UIKeyCommand *)cmd;

- (void)reset;

- (void)escCtrlSeqWithInput:(NSString *)input;
- (void)escSeqWithInput:(NSString *)input;
- (void)ctrlSeqWithInput:(NSString *)input;

@end

NS_ASSUME_NONNULL_BEGIN

@interface KeyInput : NSObject

@property (nonatomic) long long modifierFlags;
@property (nonatomic) long long keyCode;
@property (nonatomic) BOOL isKeyDown;

+ (KeyInput *)buildKeyInputFrom:(id) event;

@end


@interface UIResponder (KeyInput)

- (void)_handleKeyUIEvent:(id) event;

@end


NS_ASSUME_NONNULL_END

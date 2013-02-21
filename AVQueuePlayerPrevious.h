//
//  AVQueuePlayerPrevious.h
//  IntervalPlayer
//
//  Created by Daniel Giovannelli on 2/18/13.
//  This class subclasses AVQueuePlayer to create a class with the same functionality as AVQueuePlayer
//  but with the added ability to go backwards in the queue - a function that is impossible in a normal 
//  AVQueuePlayer since items on the queue are destroyed when they are finished playing.
//
//  IMPORTANT NOTE: This version of AVQueuePlayer assumes that ARC IS ENABLED. If ARC is NOT enabled and you
//  use this library, you'll get memory leaks on the two fields that have been added to the class, int
//  nowPlayingIndex and NSArray itemsForPlayer. If you're trying to use this in a project in which ARC is
//  NOT ENABLED, use the class AVQueuePlayerPrevious_NO_ARC, available at github.com/dgiovann
//
//  Note also that this class requires that the AVFoundation framework be included in your project.
//
// This code is released under a 2-clause BSD license, as follows:
/*Copyright (c) 2013, Daniel Giovannelli
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#import <AVFoundation/AVFoundation.h>

@interface AVQueuePlayerPrevious : AVQueuePlayer
{
    // This is a flag used to mark whether an item being added to the queue is being added by playPreviousItem (which requires slightly different functionality then in the general case) or if it is being added by an external call
    Boolean isCalledFromPlayPreviousItem;
    
    // Adding previous song functionality requires two new class variables: one array to hold the items that the player has been initialized with (to re-create the player when necessary), and one NSNumber to keep track of which song is currently playing (to determine from where the player should be re-populated
    int nowPlayingIndex;
}

@property (nonatomic, strong) NSMutableArray *itemsForPlayer;

// Two methods need to be added to the AVQueuePlayer: one which will play the last song in the queue, and one which will return if the queue is at the beginning (in case the user wishes to implement special behavior when a queue is at its first item).
-(void)playPreviousItem;
-(Boolean)isAtBeginning;

// This notification is called whenever an item finishes playing; it advances the now playing index by 1.
-(void)songEnded:(NSNotification *)notification;

/* The following methods of AVQueuePlayer are overridden by AVQueuePlayerPrevious:
 – initWithItems: to keep track of the array used to create the player
 + queuePlayerWithItems: to keep track of the array used to create the player
 – advanceToNextItem to update the now playing index
 – insertItem:afterItem: to update the now playing index
 – removeAllItems to update the now playing index
 – removeItem:  to update the now playing index
 */

@end

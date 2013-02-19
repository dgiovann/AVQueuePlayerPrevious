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
//  Note also that this classrequires that the AVFoundation framework be included in your project.

#import <AVFoundation/AVFoundation.h>

@interface AVQueuePlayerPrevious : AVQueuePlayer
{
    // Adding previous song functionality requires two new class variables: one array to hold the items that the player has been initialized with (to re-create the player when necessary), and one NSNumber to keep track of which song is currently playing (to determine from where the player should be re-populated
    int nowPlayingIndex;
}

@property (nonatomic, strong) NSMutableArray *itemsForPlayer;

// Two methods need to be added to the AVQueuePlayer: one which will play the last song in the queue, and one which will return if the queue is at the beginning (in case the user wishes to implement special behavior when a queue is at its first item).
-(void)playPreviousItem;
-(Boolean)isAtBeginning;

/* The following methods of AVQueuePlayer are overridden by AVQueuePlayerPrevious:
 – initWithItems: to keep track of the array used to create the player
 + queuePlayerWithItems: to keep track of the array used to create the player
 – advanceToNextItem to update the now playing index
 – insertItem:afterItem: to update the now playing index
 – removeAllItems to update the now playing index
 – removeItem:  to update the now playing index
 */

@end

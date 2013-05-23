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
//  nowPlayingIndex and NSArray itemsForPlayer. 
//
//  Note also that this classrequires that the AVFoundation framework be included in your project.

#import <AVFoundation/AVFoundation.h>

@interface AVQueuePlayerPrevious : AVQueuePlayer
{
    // This is a flag used to mark whether an item being added to the queue is being added by playPreviousItem (which requires slightly different functionality then in the general case) or if it is being added by an external call
    Boolean isCalledFromPlayPreviousItem;
    
    // Adding previous song functionality requires two new class variables: one array to hold the items that the player has been initialized with (to re-create the player when necessary), and one NSNumber to keep track of which song is currently playing (to determine from where the player should be re-populated
    int nowPlayingIndex;
}

@property (nonatomic, strong) NSMutableArray *itemsForPlayer;

// Two methods need to be added to the AVQueuePlayer: one which will play the last song in the queue, and one which will return if the queue is at the beginning (in case the user wishes to implement special behavior when a queue is at its first item, such as restarting a song). A getIndex method to return the current index is also provided.
-(void)playPreviousItem;
-(Boolean)isAtBeginning;
-(int)getIndex;

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

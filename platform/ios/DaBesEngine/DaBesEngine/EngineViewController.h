#import <UIKit/UIKit.h>
#import <GLKit/GLKit.h>
#import "input.h"
#import "scene.h"

@interface EngineViewController : GLKViewController <UIGestureRecognizerDelegate,
                                              GLKViewDelegate>

- (id)initWithTouchInput:(Input *)input;
- (void)didEnterBackground;
- (void)willEnterForeground;
- (void)injectMapFromPath:(NSString *)newFilePath;
- (void)restartScene;
  
@property (nonatomic, readonly) Scene *scene;
@end

#ifndef RULE_INSTANCES_H
#define RULE_INSTANCES_H

#include "constants.h"
#include "detections/detection.h"
#include "detections/detection_landing.h"
#include "detections/detection_touching.h"
#include "detections/detection_touching_without_landing.h"
#include "detections/detection_enter_window.h"

#include "reactions/reaction.h"
#include "reactions/reaction_disappear.h"
#include "reactions/reaction_player_jump.h"
#include "reactions/reaction_player_be_attacked.h"
#include "reactions/reaction_player_set_flying_state.h"
#include "reactions/reaction_make_sound.h"
#include "reactions/reaction_player_buffed_jump_height.h"
#include "reactions/reaction_player_shielded.h"
#include "reactions/reaction_gameover.h"

DetectionLanding DETECTION_LANDING;
DetectionTouching DETECTION_TOUCHING;
DetectionTouchingWithoutLanding DETECTION_TOUCHING_WITHOUT_LANDING;
DetectionEnterWindow DETECTION_ENTER_WINDOW;

ReactionDisappear REACTION_DISAPPEAR;
ReactionPlayerJump REACTION_PLAYERJUMP(-1);
ReactionPlayerJump REACTION_JUMP_SPRING(PLAYER_SPRING_JUMP_HEIGHT);
ReactionPlayerJump REACTION_JUMP_TRAMPOLINE(PLAYER_TRAMPOLINE_JUMP_HEIGHT);
ReactionPlayerJump REACTION_JUMP_PROPELLER_HAT(PLAYER_PROPELLER_HAT_JUMP_HEIGHT);
ReactionPlayerJump REACTION_JUMP_JETPACK(PLAYER_JETPACK_JUMP_HEIGHT);
ReactionPlayerJump REACTION_JUMP_SPRING_SHOES(PLAYER_SPRING_JUMP_HEIGHT);

ReactionPlayerBeAttacked REACTION_PLAYER_BE_ATTACKED;
ReactionPlayerSetFlyingState REACTION_PLAYER_SET_FLYING_STATE;

ReactionMakeSound REACTION_SOUND_BREAK("./dataset/sounds/break.wav", 80);
ReactionMakeSound REACTION_SOUND_JUMP("./dataset/sounds/jump.wav", 100);
ReactionMakeSound REACTION_SOUND_JUMP_ON_MONSTER("./dataset/sounds/jumponmonster.wav");
ReactionMakeSound REACTION_SOUND_PROPELLER("./dataset/sounds/propeller.wav");
ReactionMakeSound REACTION_SOUND_ROCKET("./dataset/sounds/rocket.wav");
ReactionMakeSound REACTION_SOUND_SPRING("./dataset/sounds/spring.wav");
ReactionMakeSound REACTION_SOUND_TRAMPOLINE("./dataset/sounds/trampoline.wav");

ReactionPlayerBuffedJumpHeight REACTION_PLAYER_BUFFED_JUMP_HEIGHT;

ReactionPlayerShielded REACTION_PLAYER_SHIELDED;
ReactionGameover REACTION_GAMEOVER;

#endif // RULE_INSTANCES_H

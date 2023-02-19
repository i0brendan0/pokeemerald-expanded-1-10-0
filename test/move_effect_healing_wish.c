#include "global.h"
#include "test_battle.h"

ASSUMPTIONS
{
    ASSUME(gBattleMoves[MOVE_HEALING_WISH].effect == EFFECT_HEALING_WISH);
    ASSUME(gBattleMoves[MOVE_LUNAR_DANCE].effect == EFFECT_HEALING_WISH);
}

#define TEST_MAX_HP (100)

SINGLE_BATTLE_TEST("Healing Wish causes the user to faint and fully heals the replacement")
{
    GIVEN {
        ASSUME(B_HEALING_WISH_SWITCH >= GEN_5);
        PLAYER(SPECIES_GARDEVOIR); // Faster than Wobbufeet.
        PLAYER(SPECIES_WYNAUT) {HP(1) ; MaxHP(TEST_MAX_HP); Status1(STATUS1_POISON); };
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_HEALING_WISH); SEND_OUT(player, 1) ; }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_HEALING_WISH, player);
        HP_BAR(player, hp: 0);
        MESSAGE("Gardevoir fainted!");
        MESSAGE("The healing wish came true for Wynaut!");
        HP_BAR(player, hp: TEST_MAX_HP);
        NOT STATUS_ICON(player, poison: TRUE);
        MESSAGE("Wynaut regained health!");
    }
}

DOUBLE_BATTLE_TEST("Lunar Dance causes the user to faint and fully heals the replacement in a double battle")
{
    GIVEN {
        ASSUME(B_HEALING_WISH_SWITCH >= GEN_5);
        PLAYER(SPECIES_GARDEVOIR); // Faster than Wobbufeet.
        PLAYER(SPECIES_WOBBUFFET);
        PLAYER(SPECIES_WYNAUT) {HP(TEST_MAX_HP - 1) ; MaxHP(TEST_MAX_HP); Status1(STATUS1_BURN); };
        OPPONENT(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_LUNAR_DANCE); SEND_OUT(playerLeft, 2) ; }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_LUNAR_DANCE, playerLeft);
        HP_BAR(playerLeft, hp: 0);
        MESSAGE("Gardevoir fainted!");
        MESSAGE("Wynaut became cloaked in mystical moonlight!");
        HP_BAR(playerLeft, hp: TEST_MAX_HP);
        NOT STATUS_ICON(playerLeft, burn: TRUE);
        MESSAGE("Wynaut regained health!");
    }
}

SINGLE_BATTLE_TEST("Healing Wish effect activates only if the switched pokemon can be healed")
{
    GIVEN {
        ASSUME(B_HEALING_WISH_SWITCH >= GEN_8);
        PLAYER(SPECIES_GARDEVOIR); // Faster than Wobbufeet.
        PLAYER(SPECIES_NINJASK); // Healthy Ninjask
        PLAYER(SPECIES_WYNAUT) {HP(TEST_MAX_HP / 2) ; MaxHP(TEST_MAX_HP); Status1(STATUS1_PARALYSIS); };
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_HEALING_WISH); SEND_OUT(player, 1) ; }
        TURN { MOVE(player, MOVE_U_TURN); SEND_OUT(player, 2) ; }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_HEALING_WISH, player);
        HP_BAR(player, hp: 0);
        MESSAGE("Gardevoir fainted!");
        NONE_OF {MESSAGE("The healing wish came true for Wynaut!") ; MESSAGE("Wynaut regained health!");};
        ANIMATION(ANIM_TYPE_MOVE, MOVE_U_TURN, player);
        MESSAGE("Do it! Wynaut!");
        MESSAGE("The healing wish came true for Wynaut!");
        HP_BAR(player, hp: TEST_MAX_HP);
        NOT STATUS_ICON(player, poison: TRUE);
        MESSAGE("Wynaut regained health!");
    }
}

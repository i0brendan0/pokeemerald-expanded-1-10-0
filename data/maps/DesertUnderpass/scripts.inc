.set LOCALID_FOSSIL, 1

DesertUnderpass_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, DesertUnderpass_OnTransition
	.byte 0

DesertUnderpass_OnTransition:
	setflag FLAG_LANDMARK_DESERT_UNDERPASS
	end

DesertUnderpass_EventScript_Fossil::
	lock
	faceplayer
    goto_if_set FLAG_PICKED_UP_OTHER_FOSSIL, DesertUnderpass_EventScript_GiveRandomFossil
    setvar VAR_0x800B, ITEM_CLAW_FOSSIL
	goto_if_set FLAG_CHOSE_ROOT_FOSSIL, DesertUnderpass_EventScript_GiveFossil
    setvar VAR_0x800B, ITEM_ROOT_FOSSIL
	goto_if_set FLAG_CHOSE_CLAW_FOSSIL, DesertUnderpass_EventScript_GiveFossil
	release
	end

DesertUnderpass_EventScript_GiveRandomFossil::
    random 7
    switch VAR_RESULT
    setvar VAR_0x800B, ITEM_HELIX_FOSSIL
    case 0, DesertUnderpass_EventScript_GiveFossil
    setvar VAR_0x800B, ITEM_DOME_FOSSIL
    case 1, DesertUnderpass_EventScript_GiveFossil
    setvar VAR_0x800B, ITEM_OLD_AMBER
    case 2, DesertUnderpass_EventScript_GiveFossil
    setvar VAR_0x800B, ITEM_ROOT_FOSSIL
    case 3, DesertUnderpass_EventScript_GiveFossil
    setvar VAR_0x800B, ITEM_CLAW_FOSSIL
    case 4, DesertUnderpass_EventScript_GiveFossil
    setvar VAR_0x800B, ITEM_SKULL_FOSSIL
    case 5, DesertUnderpass_EventScript_GiveFossil
    setvar VAR_0x800B, ITEM_ARMOR_FOSSIL
    case 6, DesertUnderpass_EventScript_GiveFossil
    release
    end
    
DesertUnderpass_EventScript_GiveFossil::
	giveitem VAR_0x800B
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	removeobject LOCALID_FOSSIL
	release
	end

@ Unused
DesertUnderpass_Text_FoundRootFossil::
	.string "{PLAYER} found the ROOT FOSSIL.$"

@ Unused
DesertUnderpass_Text_FoundClawFossil::
	.string "{PLAYER} found the CLAW FOSSIL.$"


.set LOCALID_FOSSIL_SCIENTIST, 5

RustboroCity_DevonCorp_2F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, RustboroCity_DevonCorp_2F_OnTransition
	.byte 0

RustboroCity_DevonCorp_2F_OnTransition:
	call_if_eq VAR_FOSSIL_RESURRECTION_STATE, 1, RustboroCity_DevonCorp_2F_EventScript_SetFossilReady
	end

RustboroCity_DevonCorp_2F_EventScript_SetFossilReady::
	setvar VAR_FOSSIL_RESURRECTION_STATE, 2
	return

RustboroCity_DevonCorp_2F_EventScript_TalkToPokemonScientist::
	lock
	faceplayer
	call_if_eq VAR_FOSSIL_RESURRECTION_STATE, 1, RustboroCity_DevonCorp_2F_EventScript_SetFossilReady
	msgbox RustboroCity_DevonCorp_2F_Text_DeviceForTalkingToPokemon, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_EventScript_BallScientist::
	lock
	faceplayer
	call_if_eq VAR_FOSSIL_RESURRECTION_STATE, 1, RustboroCity_DevonCorp_2F_EventScript_SetFossilReady
	goto_if_set FLAG_MET_DEVON_EMPLOYEE, RustboroCity_DevonCorp_2F_EventScript_DevelopedBalls
	msgbox RustboroCity_DevonCorp_2F_Text_DevelopingNewBalls, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_EventScript_DevelopedBalls::
	msgbox RustboroCity_DevonCorp_2F_Text_WeFinallyMadeNewBalls, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_EventScript_PokenavScientist::
	lock
	faceplayer
	call_if_eq VAR_FOSSIL_RESURRECTION_STATE, 1, RustboroCity_DevonCorp_2F_EventScript_SetFossilReady
	goto_if_set FLAG_RECEIVED_POKENAV, RustboroCity_DevonCorp_2F_EventScript_HasPokenav
	msgbox RustboroCity_DevonCorp_2F_Text_IMadePokenav, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_EventScript_HasPokenav::
	msgbox RustboroCity_DevonCorp_2F_Text_WowThatsAPokenav, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_EventScript_PokemonDreamsScientist::
	lock
	faceplayer
	call_if_eq VAR_FOSSIL_RESURRECTION_STATE, 1, RustboroCity_DevonCorp_2F_EventScript_SetFossilReady
	msgbox RustboroCity_DevonCorp_2F_Text_DeviceToVisualizePokemonDreams, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_EventScript_FossilScientist::
	lock
	faceplayer
	goto_if_eq VAR_FOSSIL_RESURRECTION_STATE, 2, RustboroCity_DevonCorp_2F_EventScript_FossilMonReady
	goto_if_eq VAR_FOSSIL_RESURRECTION_STATE, 1, RustboroCity_DevonCorp_2F_EventScript_StillRegenerating
	msgbox RustboroCity_DevonCorp_2F_Text_DevelopDeviceToResurrectFossils, MSGBOX_DEFAULT
    setvar VAR_0x800B, 0
	checkitem ITEM_HELIX_FOSSIL
    addvar VAR_0x800B, VAR_RESULT
	checkitem ITEM_DOME_FOSSIL
    addvar VAR_0x800B, VAR_RESULT
	checkitem ITEM_OLD_AMBER
    addvar VAR_0x800B, VAR_RESULT
	checkitem ITEM_ROOT_FOSSIL
    addvar VAR_0x800B, VAR_RESULT
	checkitem ITEM_CLAW_FOSSIL
    addvar VAR_0x800B, VAR_RESULT
	checkitem ITEM_SKULL_FOSSIL
    addvar VAR_0x800B, VAR_RESULT
	checkitem ITEM_ARMOR_FOSSIL
    addvar VAR_0x800B, VAR_RESULT
    goto_if_ne VAR_0x800B, 0, RustboroCity_DevonCorp_2F_EventScript_NoticeFossil
	release
	end

RustboroCity_DevonCorp_2F_EventScript_NoticeFossil::
	closemessage
	playse SE_PIN
	applymovement LOCALID_FOSSIL_SCIENTIST, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_FOSSIL_SCIENTIST, Common_Movement_Delay48
	waitmovement 0
	msgbox RustboroCity_DevonCorp_2F_Text_WantToBringFossilBackToLife, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_DevonCorp_2F_EventScript_DeclineGiveFossil
	goto_if_gt VAR_0x800B, 1, RustboroCity_DevonCorp_2F_EventScript_ChooseFossil
RustboroCity_DevonCorp_2F_EventScript_GiveOnlyFossil::
    setvar VAR_0x800B, ITEM_HELIX_FOSSIL
	checkitem ITEM_HELIX_FOSSIL
    goto_if_eq VAR_RESULT, TRUE, RustboroCity_DevonCorp_2F_EventScript_FoundFossil
    setvar VAR_0x800B, ITEM_DOME_FOSSIL
	checkitem ITEM_DOME_FOSSIL
    goto_if_eq VAR_RESULT, TRUE, RustboroCity_DevonCorp_2F_EventScript_FoundFossil
    setvar VAR_0x800B, ITEM_OLD_AMBER
	checkitem ITEM_OLD_AMBER
    goto_if_eq VAR_RESULT, TRUE, RustboroCity_DevonCorp_2F_EventScript_FoundFossil
    setvar VAR_0x800B, ITEM_ROOT_FOSSIL
	checkitem ITEM_ROOT_FOSSIL
    goto_if_eq VAR_RESULT, TRUE, RustboroCity_DevonCorp_2F_EventScript_FoundFossil
    setvar VAR_0x800B, ITEM_CLAW_FOSSIL
	checkitem ITEM_CLAW_FOSSIL
    goto_if_eq VAR_RESULT, TRUE, RustboroCity_DevonCorp_2F_EventScript_FoundFossil
    setvar VAR_0x800B, ITEM_SKULL_FOSSIL
	checkitem ITEM_SKULL_FOSSIL
    goto_if_eq VAR_RESULT, TRUE, RustboroCity_DevonCorp_2F_EventScript_FoundFossil
    setvar VAR_0x800B, ITEM_ARMOR_FOSSIL
	checkitem ITEM_ARMOR_FOSSIL
    goto_if_eq VAR_RESULT, TRUE, RustboroCity_DevonCorp_2F_EventScript_FoundFossil
    release
    end

RustboroCity_DevonCorp_2F_EventScript_FoundFossil::
    checkitem VAR_0x800B
    goto_if_eq VAR_RESULT, FALSE, RustboroCity_DevonCorp_2F_EventScript_DontHaveThisFossil
	bufferitemname STR_VAR_1, VAR_0x800B
	msgbox RustboroCity_DevonCorp_2F_Text_HandedFossilToResearcher, MSGBOX_DEFAULT
	removeitem VAR_0x800B
	setvar VAR_FOSSIL_RESURRECTION_STATE, 1
	copyvar VAR_WHICH_FOSSIL_REVIVED, VAR_0x800B
	release
	end
    
RustboroCity_DevonCorp_2F_EventScript_DontHaveThisFossil::
	msgbox RustboroCity_DevonCorp_2F_Text_DontHaveThisFossil, MSGBOX_DEFAULT
    goto RustboroCity_DevonCorp_2F_EventScript_ChooseFossil
    
RustboroCity_DevonCorp_2F_EventScript_DeclineGiveFossil::
	msgbox RustboroCity_DevonCorp_2F_Text_OhIsThatSo, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_EventScript_StillRegenerating::
	msgbox RustboroCity_DevonCorp_2F_Text_FossilRegeneratorTakesTime, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_EventScript_ChooseFossil::
	message RustboroCity_DevonCorp_2F_Text_TwoFossilsPickOne
	waitmessage
RustboroCity_DevonCorp_2F_EventScript_Gen1Fossils::
    checkitem ITEM_HELIX_FOSSIL
    call_if_eq VAR_RESULT, TRUE, RustboroCity_DevonCorp_2F_EventScript_StringVar1_Yes
    call_if_eq VAR_RESULT, FALSE, RustboroCity_DevonCorp_2F_EventScript_StringVar1_No
    checkitem ITEM_DOME_FOSSIL
    call_if_eq VAR_RESULT, TRUE, RustboroCity_DevonCorp_2F_EventScript_StringVar2_Yes
    call_if_eq VAR_RESULT, FALSE, RustboroCity_DevonCorp_2F_EventScript_StringVar2_No
    checkitem ITEM_OLD_AMBER
    call_if_eq VAR_RESULT, TRUE, RustboroCity_DevonCorp_2F_EventScript_StringVar3_Yes
    call_if_eq VAR_RESULT, FALSE, RustboroCity_DevonCorp_2F_EventScript_StringVar3_No
	multichoice 17, 6, MULTI_FOSSIL, FALSE
	switch VAR_RESULT
    setvar VAR_0x800B, ITEM_HELIX_FOSSIL
	case 0, RustboroCity_DevonCorp_2F_EventScript_FoundFossil
    setvar VAR_0x800B, ITEM_DOME_FOSSIL
	case 1, RustboroCity_DevonCorp_2F_EventScript_FoundFossil
    setvar VAR_0x800B, ITEM_OLD_AMBER
	case 2, RustboroCity_DevonCorp_2F_EventScript_FoundFossil
	case 4, RustboroCity_DevonCorp_2F_EventScript_CancelFossilSelect
	case MULTI_B_PRESSED, RustboroCity_DevonCorp_2F_EventScript_CancelFossilSelect
RustboroCity_DevonCorp_2F_EventScript_Gen3Fossils::
    checkitem ITEM_ROOT_FOSSIL
    call_if_eq VAR_RESULT, TRUE, RustboroCity_DevonCorp_2F_EventScript_StringVar1_Yes
    call_if_eq VAR_RESULT, FALSE, RustboroCity_DevonCorp_2F_EventScript_StringVar1_No
    checkitem ITEM_CLAW_FOSSIL
    call_if_eq VAR_RESULT, TRUE, RustboroCity_DevonCorp_2F_EventScript_StringVar2_Yes
    call_if_eq VAR_RESULT, FALSE, RustboroCity_DevonCorp_2F_EventScript_StringVar2_No
	multichoice 17, 6, MULTI_FOSSIL3, FALSE
	switch VAR_RESULT
    setvar VAR_0x800B, ITEM_ROOT_FOSSIL
	case 0, RustboroCity_DevonCorp_2F_EventScript_FoundFossil
    setvar VAR_0x800B, ITEM_CLAW_FOSSIL
	case 1, RustboroCity_DevonCorp_2F_EventScript_FoundFossil
	case 3, RustboroCity_DevonCorp_2F_EventScript_CancelFossilSelect
	case MULTI_B_PRESSED, RustboroCity_DevonCorp_2F_EventScript_CancelFossilSelect
RustboroCity_DevonCorp_2F_EventScript_Gen4Fossils::
    checkitem ITEM_SKULL_FOSSIL
    call_if_eq VAR_RESULT, TRUE, RustboroCity_DevonCorp_2F_EventScript_StringVar1_Yes
    call_if_eq VAR_RESULT, FALSE, RustboroCity_DevonCorp_2F_EventScript_StringVar1_No
    checkitem ITEM_ARMOR_FOSSIL
    call_if_eq VAR_RESULT, TRUE, RustboroCity_DevonCorp_2F_EventScript_StringVar2_Yes
    call_if_eq VAR_RESULT, FALSE, RustboroCity_DevonCorp_2F_EventScript_StringVar2_No
	multichoice 17, 6, MULTI_FOSSIL4, FALSE
	switch VAR_RESULT
    setvar VAR_0x800B, ITEM_SKULL_FOSSIL
	case 0, RustboroCity_DevonCorp_2F_EventScript_FoundFossil
    setvar VAR_0x800B, ITEM_ARMOR_FOSSIL
	case 1, RustboroCity_DevonCorp_2F_EventScript_FoundFossil
    case 2, RustboroCity_DevonCorp_2F_EventScript_Gen1Fossils
	case 3, RustboroCity_DevonCorp_2F_EventScript_CancelFossilSelect
	case MULTI_B_PRESSED, RustboroCity_DevonCorp_2F_EventScript_CancelFossilSelect
	end

RustboroCity_DevonCorp_2F_EventScript_StringVar1_Yes::
	bufferstring STR_VAR_1, gText_Yes
    return

RustboroCity_DevonCorp_2F_EventScript_StringVar1_No::
	bufferstring STR_VAR_1, gText_No
    return

RustboroCity_DevonCorp_2F_EventScript_StringVar2_Yes::
	bufferstring STR_VAR_2, gText_Yes
    return

RustboroCity_DevonCorp_2F_EventScript_StringVar2_No::
	bufferstring STR_VAR_2, gText_No
    return

RustboroCity_DevonCorp_2F_EventScript_StringVar3_Yes::
	bufferstring STR_VAR_3, gText_Yes
    return

RustboroCity_DevonCorp_2F_EventScript_StringVar3_No::
	bufferstring STR_VAR_3, gText_No
    return

RustboroCity_DevonCorp_2F_EventScript_CancelFossilSelect::
	release
	end

RustboroCity_DevonCorp_2F_EventScript_FossilMonReady::
    setvar VAR_0x800B, SPECIES_OMANYTE
	goto_if_eq VAR_WHICH_FOSSIL_REVIVED, ITEM_HELIX_FOSSIL, RustboroCity_DevonCorp_2F_EventScript_FossilReady
    setvar VAR_0x800B, SPECIES_KABUTO
	goto_if_eq VAR_WHICH_FOSSIL_REVIVED, ITEM_DOME_FOSSIL,  RustboroCity_DevonCorp_2F_EventScript_FossilReady
    setvar VAR_0x800B, SPECIES_AERODACTYL
	goto_if_eq VAR_WHICH_FOSSIL_REVIVED, ITEM_OLD_AMBER,    RustboroCity_DevonCorp_2F_EventScript_FossilReady
    setvar VAR_0x800B, SPECIES_LILEEP
	goto_if_eq VAR_WHICH_FOSSIL_REVIVED, ITEM_ROOT_FOSSIL,  RustboroCity_DevonCorp_2F_EventScript_FossilReady
    setvar VAR_0x800B, SPECIES_ANORITH
	goto_if_eq VAR_WHICH_FOSSIL_REVIVED, ITEM_CLAW_FOSSIL,  RustboroCity_DevonCorp_2F_EventScript_FossilReady
    setvar VAR_0x800B, SPECIES_CRANIDOS
	goto_if_eq VAR_WHICH_FOSSIL_REVIVED, ITEM_SKULL_FOSSIL, RustboroCity_DevonCorp_2F_EventScript_FossilReady
    setvar VAR_0x800B, SPECIES_SHIELDON
	goto_if_eq VAR_WHICH_FOSSIL_REVIVED, ITEM_ARMOR_FOSSIL, RustboroCity_DevonCorp_2F_EventScript_FossilReady
	end

RustboroCity_DevonCorp_2F_EventScript_FossilReady::
	bufferspeciesname STR_VAR_2, VAR_0x800B
	msgbox RustboroCity_DevonCorp_2F_Text_FossilizedMonBroughtBackToLife, MSGBOX_DEFAULT
    copyvar VAR_TEMP_TRANSFERRED_SPECIES, VAR_0x800B
    givemon VAR_0x800B, 20
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, RustboroCity_DevonCorp_2F_EventScript_ReceiveFossilParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, RustboroCity_DevonCorp_2F_EventScript_ReceiveFossilPC
	goto Common_EventScript_NoMoreRoomForPokemon
	end

RustboroCity_DevonCorp_2F_EventScript_ReceiveFossilParty::
	call RustboroCity_DevonCorp_2F_EventScript_ReceivedFossilFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_DevonCorp_2F_EventScript_FinishReceivingFossil
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto RustboroCity_DevonCorp_2F_EventScript_FinishReceivingFossil
	end

RustboroCity_DevonCorp_2F_EventScript_ReceiveFossilPC::
	call RustboroCity_DevonCorp_2F_EventScript_ReceivedFossilFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_DevonCorp_2F_EventScript_TransferFossilToPC
	call Common_EventScript_NameReceivedBoxMon
RustboroCity_DevonCorp_2F_EventScript_TransferFossilToPC::
	call Common_EventScript_TransferredToPC
	goto RustboroCity_DevonCorp_2F_EventScript_FinishReceivingFossil
	end

RustboroCity_DevonCorp_2F_EventScript_ReceivedFossilFanfare::
	bufferspeciesname STR_VAR_2, VAR_TEMP_TRANSFERRED_SPECIES
	playfanfare MUS_OBTAIN_ITEM
	message RustboroCity_DevonCorp_2F_Text_ReceivedMonFromResearcher
	waitmessage
	waitfanfare
	bufferspeciesname STR_VAR_1, VAR_TEMP_TRANSFERRED_SPECIES
	return

RustboroCity_DevonCorp_2F_EventScript_FinishReceivingFossil::
	setvar VAR_FOSSIL_RESURRECTION_STATE, 0
	setflag FLAG_RECEIVED_REVIVED_FOSSIL_MON
	release
	end

RustboroCity_DevonCorp_2F_EventScript_MatchCallScientist::
	lock
	faceplayer
	call_if_eq VAR_FOSSIL_RESURRECTION_STATE, 1, RustboroCity_DevonCorp_2F_EventScript_SetFossilReady
	goto_if_ge VAR_RUSTBORO_CITY_STATE, 6, RustboroCity_DevonCorp_2F_EventScript_WorkOnNext
	msgbox RustboroCity_DevonCorp_2F_Text_DevelopNewPokenavFeature, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_EventScript_WorkOnNext::
	msgbox RustboroCity_DevonCorp_2F_Text_WhatToWorkOnNext, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_Text_DeviceForTalkingToPokemon:
	.string "We're developing a device for talking\n"
	.string "with POKéMON.\p"
	.string "But we haven't had much success…$"

RustboroCity_DevonCorp_2F_Text_DevelopingNewBalls:
	.string "I'm developing new kinds of\n"
	.string "POKé BALLS…\p"
	.string "But I haven't made much headway…$"

RustboroCity_DevonCorp_2F_Text_WeFinallyMadeNewBalls:
	.string "We finally made new kinds of\n"
	.string "POKé BALLS!\p"
	.string "The REPEAT BALL makes it easier to\n"
	.string "catch POKéMON you've caught before.\p"
	.string "The TIMER BALL gets better at catching\n"
	.string "POKéMON the longer a battle runs.\p"
	.string "Both are proudly developed by\n"
	.string "the DEVON CORPORATION.\p"
	.string "Please give them a try!$"

RustboroCity_DevonCorp_2F_Text_IMadePokenav:
	.string "I made the POKéNAV!\p"
	.string "As an engineer, I feel blessed to have\n"
	.string "made something so great!$"

RustboroCity_DevonCorp_2F_Text_WowThatsAPokenav:
	.string "Oh, wow!\n"
	.string "That's a POKéNAV!\p"
	.string "It came about as a result of our\n"
	.string "PRESIDENT's desire to learn about\l"
	.string "the feelings of POKéMON.\p"
	.string "Would you like me to describe its\n"
	.string "features in detail?\p"
	.string "No, no. I think you'll find out just by\n"
	.string "trying the POKéNAV out.$"

RustboroCity_DevonCorp_2F_Text_DeviceToVisualizePokemonDreams:
	.string "I'm trying to develop a device that\n"
	.string "visually reproduces the dreams of\l"
	.string "POKéMON…\p"
	.string "But it's not going well.$"

RustboroCity_DevonCorp_2F_Text_DevelopDeviceToResurrectFossils:
	.string "I've been trying to develop a device\n"
	.string "that resurrects POKéMON from fossils…\p"
	.string "And, it's working!$"

RustboroCity_DevonCorp_2F_Text_WantToBringFossilBackToLife:
	.string "Wait! That thing you have there…\n"
	.string "Is that a POKéMON fossil?\p"
	.string "Would you like to bring that POKéMON\n"
	.string "back to life?\p"
	.string "I can with my newly developed\n"
	.string "FOSSIL REGENERATOR.$"

RustboroCity_DevonCorp_2F_Text_OhIsThatSo:
	.string "Oh, is that so?\p"
	.string "DEVON's technological expertise\n"
	.string "is outstanding, I tell you.$"

RustboroCity_DevonCorp_2F_Text_DontHaveThisFossil:
	.string "You don't have this fossil.\n"
	.string "Pick another kind.$"

RustboroCity_DevonCorp_2F_Text_TwoFossilsPickOne:
	.string "Unfortunately, my machine can only\n"
	.string "regenerate one POKéMON at a time.\p"
	.string "Would you like to pick one of your\n"
	.string "fossils for regeneration?$"

RustboroCity_DevonCorp_2F_Text_HandedFossilToResearcher:
	.string "Excellent!\n"
	.string "Let's do this right away.\p"
	.string "{PLAYER} handed the {STR_VAR_1} to\n"
	.string "the DEVON RESEARCHER.$"

RustboroCity_DevonCorp_2F_Text_FossilRegeneratorTakesTime:
	.string "The FOSSIL REGENERATOR, which I made,\n"
	.string "is incredible.\p"
	.string "But it has one drawback--it takes\n"
	.string "a long time to work.\p"
	.string "So, uh… How about you go for a stroll\n"
	.string "and look around for a while?$"

RustboroCity_DevonCorp_2F_Text_FossilizedMonBroughtBackToLife:
	.string "Thanks for waiting!\p"
	.string "Your fossilized POKéMON has been\n"
	.string "brought back to life!\p"
	.string "The fossil was an ancient POKéMON.\n"
	.string "{STR_VAR_2}, it was!$"

RustboroCity_DevonCorp_2F_Text_ReceivedMonFromResearcher:
	.string "{PLAYER} received {STR_VAR_2} from\n"
	.string "the DEVON RESEARCHER.$"

@ Unused
RustboroCity_DevonCorp_2F_Text_TooManyPokemon:
	.string "Uh-oh, you've got too many POKéMON.\n"
	.string "You have no room for this one.$"

RustboroCity_DevonCorp_2F_Text_DevelopNewPokenavFeature:
	.string "I'm trying to develop a new feature\n"
	.string "for the POKéNAV…\p"
	.string "But it's not going well.$"

RustboroCity_DevonCorp_2F_Text_WhatToWorkOnNext:
	.string "Well, now what shall I work on\n"
	.string "developing next?\p"
	.string "Our company allows us to make our\n"
	.string "inspirations into reality.\p"
	.string "One couldn't ask for a better\n"
	.string "environment as an engineer.$"


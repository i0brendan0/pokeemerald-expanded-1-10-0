FallarborTown_CozmosHouse_MapScripts::
	.byte 0

FallarborTown_CozmosHouse_EventScript_ProfCozmo::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM_RETURN, FallarborTown_CozmosHouse_EventScript_GaveMeteorite
	checkitem ITEM_METEORITE
	goto_if_eq VAR_RESULT, TRUE, FallarborTown_CozmosHouse_EventScript_PlayerHasMeteorite
	msgbox FallarborTown_CozmosHouse_Text_MeteoriteWillNeverBeMineNow, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_PlayerHasMeteorite::
	call_if_unset FLAG_TEMP_2, FallarborTown_CozmosHouse_EventScript_NoticeMeteorite
	call_if_set FLAG_TEMP_2, FallarborTown_CozmosHouse_EventScript_AskForMeteorite
	goto_if_eq VAR_RESULT, NO, FallarborTown_CozmosHouse_EventScript_DeclineGiveMeteorite
	msgbox FallarborTown_CozmosHouse_Text_PleaseUseThisTM, MSGBOX_DEFAULT
	giveitem ITEM_TM_RETURN
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setvar VAR_0x8004, ITEM_METEORITE
	call Common_EventScript_PlayerHandedOverTheItem
	setflag FLAG_RECEIVED_TM_RETURN
	msgbox FallarborTown_CozmosHouse_Text_ReallyGoingToHelpMyResearch, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_NoticeMeteorite::
	msgbox FallarborTown_CozmosHouse_Text_MeteoriteWillNeverBeMineNow, MSGBOX_DEFAULT
	msgbox FallarborTown_CozmosHouse_Text_IsThatMeteoriteMayIHaveIt, MSGBOX_YESNO
	return

FallarborTown_CozmosHouse_EventScript_AskForMeteorite::
	msgbox FallarborTown_CozmosHouse_Text_MayIHaveMeteorite, MSGBOX_YESNO
	return

FallarborTown_CozmosHouse_EventScript_DeclineGiveMeteorite::
	setflag FLAG_TEMP_2
	msgbox FallarborTown_CozmosHouse_Text_CrushedWithDisappointment, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_GaveMeteorite::
    goto_if_set FLAG_BATTLED_DEOXYS, FallarborTown_CozmosHouse_EventScript_GiveBackMeteorite
FallarborTown_CozmosHouse_EventScript_NoDeoxysInParty::
	msgbox FallarborTown_CozmosHouse_Text_ReallyGoingToHelpMyResearch, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_GiveBackMeteorite::
    goto_if_set FLAG_GAVE_BACK_METEORITE, FallarborTown_CozmosHouse_EventScript_GaveBackMeteorite
    checkspecies SPECIES_DEOXYS
	goto_if_eq VAR_RESULT, FALSE, FallarborTown_CozmosHouse_EventScript_NoDeoxysInParty
    msgbox FallarborTown_CozmosHouse_Text_PlayerHasDeoxys, MSGBOX_DEFAULT
    giveitem ITEM_METEORITE
    goto_if_eq VAR_RESULT, FALSE, FallarborTown_CozmosHouse_EventScript_CantGetMeteorite
    setflag FLAG_GAVE_BACK_METEORITE
    msgbox FallarborTown_CozmosHouse_Text_GivenMeteoriteBack
    release
    end
    
FallarborTown_CozmosHouse_EventScript_GaveBackMeteorite::
    msgbox FallarborTown_CozmosHouse_Text_TalkAboutMeteorite, MSGBOX_DEFAULT
    release
    end

FallarborTown_CozmosHouse_EventScript_CantGetMeteorite::
    msgbox FallarborTown_CozmosHouse_Text_CantGetMeteorite, MSGBOX_DEFAULT
    release
    end

FallarborTown_CozmosHouse_Text_PlayerHasDeoxys::
	.string "PROF. COZMO: Oh…\p"
	.string "Is that…\n"
    .string "a DEOXYS you have with you?\p"
	.string "Wow. I never thought I would see one.\n"
	.string "I've heard that DEOXYS can change\l"
	.string "form with a METEORITE.\p"
	.string "Why don't you take the METEORITE\n"
	.string "back and see what you can do with it.\l"
	.string "I've already done every test on it\l"
    .string "that I could think of.$"

FallarborTown_CozmosHouse_Text_GivenMeteoriteBack::
    .string "There you go.\n"
    .string "Now try it out on your DEOXYS\l"
    .string "and see what happens.$"
    
FallarborTown_CozmosHouse_Text_TalkAboutMeteorite::
	.string "PROF. COZMO: How is the METEORITE\n"
	.string "working out for you?\l"
	.string "I hope you're getting some use\l"
	.string "out of it since I gave it back.$"

FallarborTown_CozmosHouse_Text_CantGetMeteorite::
	.string "PROF. COZMO: Oh…\n"
	.string "It looks like you'll need to make\l"
	.string "room for the METEORITE. Otherwise,\l"
	.string "I can't give it to you.$"

FallarborTown_CozmosHouse_EventScript_CozmosWife::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM_RETURN, FallarborTown_CozmosHouse_EventScript_CozmoIsHappy
	goto_if_set FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY, FallarborTown_CozmosHouse_EventScript_CozmoIsSad
	msgbox FallarborTown_CozmosHouse_Text_CozmoWentToMeteorFalls, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_CozmoIsSad::
	msgbox FallarborTown_CozmosHouse_Text_FeelSorryForCozmo, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_CozmoIsHappy::
	msgbox FallarborTown_CozmosHouse_Text_CozmoIsSoHappy, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_Text_MeteoriteWillNeverBeMineNow:
	.string "PROF. COZMO: Oh…\n"
	.string "I never should have let myself be\l"
	.string "conned into telling TEAM MAGMA where\l"
	.string "you can find METEORITES…\p"
	.string "That METEORITE from METEOR FALLS…\n"
	.string "It's never going to be mine now…$"

FallarborTown_CozmosHouse_Text_IsThatMeteoriteMayIHaveIt:
	.string "Oh!\n"
	.string "Hah?\p"
	.string "That item…\p"
	.string "Could it be?\p"
	.string "Is it the METEORITE that TEAM MAGMA\n"
	.string "took from METEOR FALLS?\p"
	.string "Please, may I have it?\p"
	.string "I'm not asking for it for free.\n"
	.string "How about in exchange for this TM?$"

FallarborTown_CozmosHouse_Text_PleaseUseThisTM:
	.string "PROF. COZMO: This TM, it represents\n"
	.string "my feeling of gratitude.\l"
	.string "Please use it!$"

FallarborTown_CozmosHouse_Text_ReallyGoingToHelpMyResearch:
	.string "PROF. COZMO: Oh, I can't believe it.\n"
	.string "This is really, really great!\p"
	.string "This is really going to help my research!$"

FallarborTown_CozmosHouse_Text_CrushedWithDisappointment:
	.string "PROF. COZMO: Oh, but…\n"
	.string "I'm crushed with disappointment…$"

FallarborTown_CozmosHouse_Text_MayIHaveMeteorite:
	.string "PROF. COZMO: Please, may I have that\n"
	.string "METEORITE?\p"
	.string "I'm not asking for it for free.\n"
	.string "How about in exchange for this TM?$"

FallarborTown_CozmosHouse_Text_CozmoWentToMeteorFalls:
	.string "PROF. COZMO went off to METEOR FALLS\n"
	.string "on ROUTE 114 with some people from\l"
	.string "TEAM MAGMA.$"

FallarborTown_CozmosHouse_Text_FeelSorryForCozmo:
	.string "Poor PROF. COZMO…\n"
	.string "He's so depressed… I feel sorry for him.$"

FallarborTown_CozmosHouse_Text_CozmoIsSoHappy:
	.string "Look at PROF. COZMO…\n"
	.string "He's so happy! I think it's cute.$"


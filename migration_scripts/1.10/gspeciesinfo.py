import re
import glob
import os

label_renames = [
    ["Alolan", "Alola", "ALOLAN", "ALOLA"],
    ["Galarian", "Galar", "GALARIAN", "GALAR"],
    ["Hisuian", "Hisui", "HISUIAN", "HISUI"],
    ["Paldean", "Paldea", "PALDEAN", "PALDEA"],
]

if not os.path.exists("Makefile"):
    print("Please run this script from your root folder.")
    quit()

# Read front_pic_anims.h
for file in glob.glob('./src/data/pokemon_graphics/front_pic_anims.h'):
    with open(file, 'r') as f:
        anim_table_content = f.read()

# Read existing animations present to avoid removing shared animations
anim_table_data = {}
shared_anim_table_data = {}
pattern = re.compile(r'\.frontAnimFrames = sAnims_(\w+),', re.DOTALL)
for gen in range(1,10):
    for file in glob.glob('./src/data/pokemon/species_info/gen_%d_families.h' % gen):
        with open(file, 'r') as f:
            species_content = f.read()
        for match in pattern.findall(species_content):
            if match in anim_table_data:
                if match not in shared_anim_table_data:
                    shared_anim_table_data[match] = match
            else:
                anim_table_data[match] = match

# Extract animation data from front_pic_anims.h
anim_table_pattern = re.compile(r'static const union AnimCmd sAnim_(\w+)_1\[\] =\n\{\n((    (ANIMCMD_FRAME\(\d+ *, \d+ *\)|ANIMCMD_LOOP\(\d+\)),\n){1,})    ANIMCMD_END,\n\};', re.MULTILINE)
anim_table_data = {}
for match in anim_table_pattern.findall(anim_table_content):
    if len(match) == 4:
        anim_name, anim_frames, unused1, unused2, = match
        anim_table_data[anim_name] = (anim_frames)

# Extract single-frame placeholder animations from front_pic_anims.h
single_placeholder_pattern = re.compile(r'PLACEHOLDER_ANIM_SINGLE_FRAME\((\w+)\);', re.MULTILINE)
single_placeholder_data = {}
for match in single_placeholder_pattern.findall(anim_table_content):
    anim_name = match
    single_placeholder_data[anim_name] = (anim_name)

# Extract 2-frame placeholder animations from front_pic_anims.h
double_placeholder_pattern = re.compile(r'PLACEHOLDER_ANIM_TWO_FRAMES\((\w+)\);', re.MULTILINE)
double_placeholder_data = {}
for match in double_placeholder_pattern.findall(anim_table_content):
    anim_name = match
    double_placeholder_data[anim_name] = (anim_name)

# Read pokemon_jump.c
for file in glob.glob('./src/pokemon_jump.c'):
    with open(file, 'r') as f:
        pokemon_jump_content = f.read()
pokemon_jump_pattern = re.compile(r'\{ \.species = SPECIES_(\w+), *\.jumpType = JUMP_TYPE_(\w+), \},', re.MULTILINE)
pokemon_jump_data = {}
for match in pokemon_jump_pattern.findall(pokemon_jump_content):
    if len(match) == 2:
        mon_name, jump_type = match
        pokemon_jump_data[mon_name] = (jump_type)

# Trackers
updated = False
issuesCounter = 0

# Modify gen_X_families.h's animation content
def add_anim_data(match):
    global updated
    global issuesCounter
    mon_name = match.group(1)
    if mon_name in anim_table_data and mon_name not in shared_anim_table_data:
        anim_frames = anim_table_data[mon_name]
        anim_frames = re.sub('    ANIMCMD_FRAME\(', '            ANIMCMD_FRAME(', anim_frames)
        updated = True
        return f'.frontAnimFrames = ANIM_FRAMES(\n{anim_frames}        ),'
    elif mon_name in single_placeholder_data:
        updated = True
        return f'.frontAnimFrames = sAnims_SingleFramePlaceHolder,'
    elif mon_name in double_placeholder_data:
        updated = True
        return f'.frontAnimFrames = sAnims_TwoFramePlaceHolder,'
    else:
        if mon_name != 'SingleFramePlaceHolder' and mon_name != 'TwoFramePlaceHolder' and mon_name not in shared_anim_table_data:
            print(f"\n - {mon_name} animations were NOT updated.", end="")
            issuesCounter = issuesCounter + 1
        return f'.frontAnimFrames = sAnims_{mon_name},'

def update_basic_follower_data(match):
    global updated
    global issuesCounter

    # Alignment spaces
    sp1 = "        "
    sp = "            "
    mon_name1 = match.group(1)
    size = match.group(2)
    shadow = match.group(3)
    footprint = match.group(4)
    mon_name2 = match.group(5)
    mon_name3 = match.group(6)

    return f'{sp1}OVERWORLD(\n{sp}gObjectEventPic_{mon_name1},\n{sp}SIZE_{size},\n{sp}SHADOW_SIZE_{shadow},\n{sp}TRACKS_{footprint},\n{sp}sAnimTable_Following,\n{sp}gOverworldPalette_{mon_name2},\n{sp}gShinyOverworldPalette_{mon_name3}\n{sp1})'

def update_set_anim_follower_data(match):
    global updated
    global issuesCounter

    # Alignment spaces
    sp1 = "        "
    sp = "            "
    mon_name1 = match.group(1)
    size = match.group(2)
    shadow = match.group(3)
    footprint = match.group(4)
    setAnim = match.group(5)
    mon_name2 = match.group(6)
    mon_name3 = match.group(7)

    return f'{sp1}OVERWORLD(\n{sp}gObjectEventPic_{mon_name1},\n{sp}SIZE_{size},\n{sp}SHADOW_SIZE_{shadow},\n{sp}TRACKS_{footprint},\n{sp}{setAnim},\n{sp}gOverworldPalette_{mon_name2},\n{sp}gShinyOverworldPalette_{mon_name3}\n{sp1})'

def add_jump_data(match):
    global updated
    global issuesCounter
    brace = "{"
    mon_name = match.group(1)
    in_bewteen_rows = match.group(2)
    iconPalIndex = match.group(4)
    if mon_name in pokemon_jump_data:
        updated = True
        return f'    [SPECIES_{mon_name}] =\n    {brace}\n{in_bewteen_rows}        .iconPalIndex = {iconPalIndex},\n        .pokemonJumpType = PKMN_JUMP_TYPE_' + pokemon_jump_data[mon_name] + f',\n        FOOTPRINT'
    else:
        return f'    [SPECIES_{mon_name}] =\n    {brace}\n{in_bewteen_rows}        .iconPalIndex = {iconPalIndex},\n        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,\n        FOOTPRINT'

for gen in range(1,10):
    updated = False
    issuesCounter = 0
    print("\ngen_%d_families.h" % gen, end =" ")
    # Read gen_X_families.h content
    for file in glob.glob('./src/data/pokemon/species_info/gen_%d_families.h' % gen):
        with open(file, 'r') as f:
            species_content = f.read()

    original_species_content = species_content

    # Alter front animations
    pattern = re.compile(r'\.frontAnimFrames = sAnims_(\w+),', re.DOTALL)
    species_content = pattern.sub(add_anim_data, species_content)
    
    # Alter follower data
    pattern = re.compile(r' {8}OVERWORLD\(\n {12}sPicTable_(\w+),\n {12}SIZE_(\w+),\n {12}SHADOW_SIZE_(\w+),\n {12}TRACKS_(\w+),\n {12}gOverworldPalette_(\w+),\n {12}gShinyOverworldPalette_(\w+)\n {8}\)', re.MULTILINE)
    species_content = pattern.sub(update_basic_follower_data, species_content)
    pattern = re.compile(r' {8}OVERWORLD_SET_ANIM\(\n {12}sPicTable_(\w+),\n {12}SIZE_(\w+),\n {12}SHADOW_SIZE_(\w+),\n {12}TRACKS_(\w+),\n {12}(\w+),\n {12}gOverworldPalette_(\w+),\n {12}gShinyOverworldPalette_(\w+)\n {8}\)', re.MULTILINE)
    species_content = pattern.sub(update_set_anim_follower_data, species_content)

    # Alter Pokémon Jump data
    pattern = re.compile(r'    \[SPECIES_(\w+)\] =\n    \{\n((.*\n){1,}?)        \.iconPalIndex = (.*),\n        FOOTPRINT', re.MULTILINE)
    species_content = pattern.sub(add_jump_data, species_content)

    # Rename form labels and defines
    for form_labels in label_renames:
        species_content = re.sub(r"(gMonFrontPic_|gMonBackPic_|gMonPalette_|gMonShinyPalette_|gMonIcon_)(\w+)" + form_labels[0], r"\1\2" + form_labels[1], species_content)
        species_content = re.sub(r"(gObjectEventPic_|gOverworldPalette_|gShinyOverworldPalette_)(\w+)" + form_labels[0], r"\1\2" + form_labels[1], species_content)
        species_content = re.sub(r"s(\w+)" + form_labels[0] + r"(LevelUp|Teachable|EggMove)Learnset", r"s\1" + form_labels[1] + r"\2Learnset", species_content)
        species_content = re.sub(r"g(\w+)" + form_labels[0] + r"PokedexText", r"g\1" + form_labels[1] + r"PokedexText", species_content)
        species_content = re.sub(r"SPECIES_(\w+)_" + form_labels[2] + r"", r"SPECIES_\1_" + form_labels[3] + r"", species_content)

    if (species_content != original_species_content):
        updated = True

    if updated:
        # Write the modified content back to gen_X_families.h
        for file in glob.glob('./src/data/pokemon/species_info/gen_%d_families.h' % gen):
            with open(file, 'w') as f:
                f.write(species_content)
        print("was updated.", end="")
    elif issuesCounter == 0:
        print("was NOT updated.", end="")

print("")

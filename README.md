# Emerald EM

![badge-version](https://img.shields.io/github/v/release/Nax/emerald-em?include_prereleases)
![badge-license](https://img.shields.io/badge/license-MIT-brightgreen)
![badge-build](https://img.shields.io/github/actions/workflow/status/Nax/emerald-em/ci.yml?branch=master)
![badge-stars](https://img.shields.io/github/stars/Nax/emerald-em)
![badge-downloads](https://img.shields.io/github/downloads/Nax/emerald-em/total)

<p align="center">A randomizer for Pokémon Emerald that includes all content up to the 9th generation.</p>
<p align="center">
  <img with="100%" height="100%" src="https://raw.githubusercontent.com/Nax/emerald-em/master/doc/images/ShufflerExample.png" alt="Emerald-EM GUI"/>
</p>

## Overview

Emerald-EM is a Pokémon Emerald randomizer that allows you to play the game with all content up to the 9th generation, such as:

- Pokémon, including forms
- Abilities
- Moves
- Items
- Fairy Type
- Physical/Special Split
- Mega Evolutions, Primal Reversion, Z-Moves
- Etc.

It is intended to be used for "ironmon"-type challenges. For that purpose, the following things are randomized:

- Starting Pokémon
- Wild Pokémon
- Trainer Pokémon
- Pokémon stats
- Pokémon moves
- Pokémon abilities
- Items
- TMs/HMs

Also, a translation system is included if you want to play in a different language.
So far the only supported languages are English and French (partial).

## Changes to the original game

- HM moves are no longer required or usable by themselves. Instead, you can press use them naturally when having the proper badge.
- Flash will automatically be used in dark caves.
- Fly can be used by opening the map, which is a key item that you start with.

## How to use

1. Download the latest release from the [releases page](https://github.com/Nax/emerald-em/releases).
2. Extract the archive somewhere on your computer.
3. Open the `Shuffler-GUI.exe` file.
4. Select your original ROM. It must be a clean Pokémon Emerald (U) ROM.
5. Select the destination folder where the randomized ROM will be created.
6. Press the "Generate" button.

Once the randomization is done, a file named `Emerald-EM-Seed.gba` will be created in the destination folder.
You can now play the randomized ROM using a GBA emulator or flashcart.
We recommend using [mGBA](https://mgba.io/).

## License

Emerald-EM (and only Emerald-EM, not the pokeemerald-expansion code under `emerald/`) is licensed under the MIT License.

## Author

Emerald-EM is developped by [Maxime Bacoux "Nax"](https://github.com/Nax).

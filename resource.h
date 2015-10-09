#define PLUG_MFR "DanCat"
#define PLUG_NAME "Vega"

#define PLUG_CLASS_NAME Vega

#define BUNDLE_MFR "DanCat"
#define BUNDLE_NAME "Vega"

#define PLUG_ENTRY Vega_Entry
#define PLUG_VIEW_ENTRY Vega_ViewEntry

#define PLUG_ENTRY_STR "Vega_Entry"
#define PLUG_VIEW_ENTRY_STR "Vega_ViewEntry"

#define VIEW_CLASS Vega_View
#define VIEW_CLASS_STR "Vega_View"

// Format        0xMAJR.MN.BG - in HEX! so version 10.1.5 would be 0x000A0105
#define PLUG_VER 0x00010000
#define VST3_VER_STR "1.0.0"

// http://service.steinberg.de/databases/plugin.nsf/plugIn?openForm
// 4 chars, single quotes. At least one capital letter
#define PLUG_UNIQUE_ID 'Ipef'
// make sure this is not the same as BUNDLE_MFR
#define PLUG_MFR_ID 'Acme'

// ProTools stuff

#if (defined(AAX_API) || defined(RTAS_API)) && !defined(_PIDS_)
  #define _PIDS_
  const int PLUG_TYPE_IDS[2] = {'EFN1', 'EFN2'};
  const int PLUG_TYPE_IDS_AS[2] = {'EFA1', 'EFA2'}; // AudioSuite
#endif

#define PLUG_MFR_PT "DanCat\nDanCat\nAcme"
#define PLUG_NAME_PT "Vega\nIPEF"
#define PLUG_TYPE_PT "None"
#define PLUG_DOES_AUDIOSUITE 1

/* PLUG_TYPE_PT can be "None", "EQ", "Dynamics", "PitchShift", "Reverb", "Delay", "Modulation", 
"Harmonic" "NoiseReduction" "Dither" "SoundField" "Effect" 
instrument determined by PLUG _IS _INST
*/

// #define PLUG_CHANNEL_IO "1-1 2-2"
#if (defined(AAX_API) || defined(RTAS_API)) 
#define PLUG_CHANNEL_IO "1-1 2-2"
#else
// no audio input. mono or stereo output
#define PLUG_CHANNEL_IO "0-1 0-2"
#endif

#define PLUG_LATENCY 0
#define PLUG_IS_INST 1

// if this is 0 RTAS can't get tempo info
#define PLUG_DOES_MIDI 1

#define PLUG_DOES_STATE_CHUNKS 0

// Unique IDs for each image resource.
#define KNOB_ID 101
#define BACKGROUND_ID 102
#define PIANO_BLK_ID 103
#define PIANO_WHT_ID 104
#define PASS_ID 105
#define SLIDER_ID 106
#define VOICES_ID 107
#define SLOPE_ID 108
#define WAVE_ID 109
#define OCTAVE_ID 110
#define BUTTON_ID 111
#define ADD_ID 112
#define NOTE_ID 113
#define MINIKNOB_ID 114
#define PITCHMOD_ID 115

// Image resource locations for this plug.
#define KNOB_FN "resources/img/VegaKnob.png"
#define BACKGROUND_FN "resources/img/VegaClearBG.png"
#define PIANO_BLK_FN "resources/img/BlackKeyPressed.png"
#define PIANO_WHT_FN "resources/img/WhiteKeysPressed.png"
#define PASS_FN "resources/img/PassSwitch.png"
#define SLIDER_FN "resources/img/VegaSlider.png"
#define VOICES_FN "resources/img/Voices.png"
#define SLOPE_FN "resources/img/Slope.png"
#define WAVE_FN "resources/img/Waves.png"
#define OCTAVE_FN "resources/img/Octave.png"
#define BUTTON_FN "resources/img/filtermode.png"
#define ADD_FN "resources/img/filtermode.png"
#define NOTE_FN "resources/img/Note.png"
#define MINIKNOB_FN "resources/img/VegaMiniKnob.png"
#define PITCHMOD_FN "resources/img/BendWheel.png"

// GUI default dimensions
#define GUI_WIDTH 880
#define GUI_HEIGHT 560

// on MSVC, you must define SA_API in the resource editor preprocessor macros as well as the c++ ones
#if defined(SA_API) && !defined(OS_IOS)
#include "app_wrapper/app_resource.h"
#endif

// vst3 stuff
#define MFR_URL "www.olilarkin.co.uk"
#define MFR_EMAIL "spam@me.com"
#define EFFECT_TYPE_VST3 "Instrument|Synth"

/* "Fx|Analyzer"", "Fx|Delay", "Fx|Distortion", "Fx|Dynamics", "Fx|EQ", "Fx|Filter",
"Fx", "Fx|Instrument", "Fx|InstrumentExternal", "Fx|Spatial", "Fx|Generator",
"Fx|Mastering", "Fx|Modulation", "Fx|PitchShift", "Fx|Restoration", "Fx|Reverb",
"Fx|Surround", "Fx|Tools", "Instrument", "Instrument|Drum", "Instrument|Sampler",
"Instrument|Synth", "Instrument|Synth|Sampler", "Instrument|External", "Spatial",
"Spatial|Fx", "OnlyRT", "OnlyOfflineProcess", "Mono", "Stereo",
"Surround"
*/

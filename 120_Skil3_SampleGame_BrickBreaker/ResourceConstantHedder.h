#pragma once



//------------------------------------------------------------------------------------------------------------------
// 
// file path 
// 


constexpr const char* FILE_PATH_CSV_EXAMPLE = "resource/csv/example.csv"; 
constexpr const char* FILE_PATH_CSV_EXAMPLE_MAP_CHIP = "resource/csv/example_map_chip.csv"; 

constexpr const char* FILE_PATH_BIN_DIRECTIONAL_LIGHT_PARAMETER = "resource/dxe_parameters/directional_light/directional_light_parameter.bin"; 

constexpr const char* FILE_PATH_BIN_GRAPHICS_LAYER_STATUS = "resource/dxe_parameters/graphics_layer/graphics_layer_status.bin"; 

constexpr const char* FILE_PATH_BIN_MATERIAL = "resource/dxe_parameters/mesh_material/material.bin"; 

constexpr const char* FILE_PATH_BIN_CONVERGENCE = "resource/dxe_parameters/particle/preset/convergence.bin"; 
constexpr const char* FILE_PATH_BIN_DEFAULT = "resource/dxe_parameters/particle/preset/default.bin"; 
constexpr const char* FILE_PATH_BIN_EXPLOSION = "resource/dxe_parameters/particle/preset/explosion.bin"; 
constexpr const char* FILE_PATH_BIN_FIRE = "resource/dxe_parameters/particle/preset/fire.bin"; 
constexpr const char* FILE_PATH_BIN_FIREWORKS = "resource/dxe_parameters/particle/preset/fireworks.bin"; 
constexpr const char* FILE_PATH_BIN_RAIN = "resource/dxe_parameters/particle/preset/rain.bin"; 
constexpr const char* FILE_PATH_BIN_RAIN_GROUND = "resource/dxe_parameters/particle/preset/rain_ground.bin"; 
constexpr const char* FILE_PATH_BIN_SMOKE = "resource/dxe_parameters/particle/preset/smoke.bin"; 
constexpr const char* FILE_PATH_BIN_SNOW = "resource/dxe_parameters/particle/preset/snow.bin"; 
constexpr const char* FILE_PATH_BIN_WATER_FALL = "resource/dxe_parameters/particle/preset/water_fall.bin"; 

constexpr const char* FILE_PATH_BIN_SKYBOX_MATERIAL = "resource/dxe_parameters/skybox_material/skybox_material.bin"; 

constexpr const char* FILE_PATH_BIN_WATER_PLANE = "resource/dxe_parameters/water_plane/water_plane.bin"; 

constexpr const char* FILE_PATH_OTF_03TAKIBI_REGULAR = "resource/font/03Takibi-Regular.otf"; 
constexpr const char* FILE_PATH_OTF_CORPORATE_LOGO_ROUNDED_BOLD_VER3 = "resource/font/Corporate-Logo-Rounded-Bold-ver3.otf"; 

constexpr const char* FILE_PATH_PNG_BAR = "resource/graphics/bar.png"; 
constexpr const char* FILE_PATH_PNG_BLACK1 = "resource/graphics/black1.png"; 
constexpr const char* FILE_PATH_PNG_BLOCK = "resource/graphics/block.png"; 

constexpr const char* FILE_PATH_JSON_EXAMPLE = "resource/json/example.json"; 

constexpr const char* FILE_PATH_PSO_EREA_PROJECTION = "resource/shader/dxe/erea_projection.pso"; 
constexpr const char* FILE_PATH_VSO_EREA_PROJECTION = "resource/shader/dxe/erea_projection.vso"; 

constexpr const char* FILE_PATH_MP3_SE_SAMPLE_0 = "resource/sound/example/se_sample_0.mp3"; 



//------------------------------------------------------------------------------------------------------------------
// 
// file path table 
// 


const std::vector<const char*> FILE_PATH_TBL_CSV = {
    FILE_PATH_CSV_EXAMPLE,
    FILE_PATH_CSV_EXAMPLE_MAP_CHIP,
};
const std::vector<const char*> FILE_PATH_TBL_DXE_PARAMETERS_DIRECTIONAL_LIGHT = {
    FILE_PATH_BIN_DIRECTIONAL_LIGHT_PARAMETER,
};
const std::vector<const char*> FILE_PATH_TBL_DXE_PARAMETERS_GRAPHICS_LAYER = {
    FILE_PATH_BIN_GRAPHICS_LAYER_STATUS,
};
const std::vector<const char*> FILE_PATH_TBL_DXE_PARAMETERS_MESH_MATERIAL = {
    FILE_PATH_BIN_MATERIAL,
};
const std::vector<const char*> FILE_PATH_TBL_DXE_PARAMETERS_PARTICLE_PRESET = {
    FILE_PATH_BIN_CONVERGENCE,
    FILE_PATH_BIN_DEFAULT,
    FILE_PATH_BIN_EXPLOSION,
    FILE_PATH_BIN_FIRE,
    FILE_PATH_BIN_FIREWORKS,
    FILE_PATH_BIN_RAIN,
    FILE_PATH_BIN_RAIN_GROUND,
    FILE_PATH_BIN_SMOKE,
    FILE_PATH_BIN_SNOW,
    FILE_PATH_BIN_WATER_FALL,
};
const std::vector<const char*> FILE_PATH_TBL_DXE_PARAMETERS_SKYBOX_MATERIAL = {
    FILE_PATH_BIN_SKYBOX_MATERIAL,
};
const std::vector<const char*> FILE_PATH_TBL_DXE_PARAMETERS_WATER_PLANE = {
    FILE_PATH_BIN_WATER_PLANE,
};
const std::vector<const char*> FILE_PATH_TBL_FONT = {
    FILE_PATH_OTF_03TAKIBI_REGULAR,
    FILE_PATH_OTF_CORPORATE_LOGO_ROUNDED_BOLD_VER3,
};
const std::vector<const char*> FILE_PATH_TBL_GRAPHICS = {
    FILE_PATH_PNG_BAR,
    FILE_PATH_PNG_BLACK1,
    FILE_PATH_PNG_BLOCK,
};
const std::vector<const char*> FILE_PATH_TBL_JSON = {
    FILE_PATH_JSON_EXAMPLE,
};
const std::vector<const char*> FILE_PATH_TBL_SHADER_DXE = {
    FILE_PATH_PSO_EREA_PROJECTION,
    FILE_PATH_VSO_EREA_PROJECTION,
};
const std::vector<const char*> FILE_PATH_TBL_SOUND_EXAMPLE = {
    FILE_PATH_MP3_SE_SAMPLE_0,
};


//------------------------------------------------------------------------------------------------------------------
// 
// file path map 
// 


const std::unordered_map<std::string, const char*> FILE_PATH_DICTIONARY = { 
    { std::string( "example.csv" ), FILE_PATH_CSV_EXAMPLE },
    { std::string( "example_map_chip.csv" ), FILE_PATH_CSV_EXAMPLE_MAP_CHIP },
    { std::string( "directional_light_parameter.bin" ), FILE_PATH_BIN_DIRECTIONAL_LIGHT_PARAMETER },
    { std::string( "graphics_layer_status.bin" ), FILE_PATH_BIN_GRAPHICS_LAYER_STATUS },
    { std::string( "material.bin" ), FILE_PATH_BIN_MATERIAL },
    { std::string( "convergence.bin" ), FILE_PATH_BIN_CONVERGENCE },
    { std::string( "default.bin" ), FILE_PATH_BIN_DEFAULT },
    { std::string( "explosion.bin" ), FILE_PATH_BIN_EXPLOSION },
    { std::string( "fire.bin" ), FILE_PATH_BIN_FIRE },
    { std::string( "fireworks.bin" ), FILE_PATH_BIN_FIREWORKS },
    { std::string( "rain.bin" ), FILE_PATH_BIN_RAIN },
    { std::string( "rain_ground.bin" ), FILE_PATH_BIN_RAIN_GROUND },
    { std::string( "smoke.bin" ), FILE_PATH_BIN_SMOKE },
    { std::string( "snow.bin" ), FILE_PATH_BIN_SNOW },
    { std::string( "water_fall.bin" ), FILE_PATH_BIN_WATER_FALL },
    { std::string( "skybox_material.bin" ), FILE_PATH_BIN_SKYBOX_MATERIAL },
    { std::string( "water_plane.bin" ), FILE_PATH_BIN_WATER_PLANE },
    { std::string( "03Takibi-Regular.otf" ), FILE_PATH_OTF_03TAKIBI_REGULAR },
    { std::string( "Corporate-Logo-Rounded-Bold-ver3.otf" ), FILE_PATH_OTF_CORPORATE_LOGO_ROUNDED_BOLD_VER3 },
    { std::string( "bar.png" ), FILE_PATH_PNG_BAR },
    { std::string( "black1.png" ), FILE_PATH_PNG_BLACK1 },
    { std::string( "block.png" ), FILE_PATH_PNG_BLOCK },
    { std::string( "example.json" ), FILE_PATH_JSON_EXAMPLE },
    { std::string( "erea_projection.pso" ), FILE_PATH_PSO_EREA_PROJECTION },
    { std::string( "erea_projection.vso" ), FILE_PATH_VSO_EREA_PROJECTION },
    { std::string( "se_sample_0.mp3" ), FILE_PATH_MP3_SE_SAMPLE_0 },
};


//------------------------------------------------------------------------------------------------------------------
// 
// file name 
// 


constexpr const char* FILE_NAME_CSV_EXAMPLE = "example.csv"; 
constexpr const char* FILE_NAME_CSV_EXAMPLE_MAP_CHIP = "example_map_chip.csv"; 

constexpr const char* FILE_NAME_BIN_DIRECTIONAL_LIGHT_PARAMETER = "directional_light_parameter.bin"; 

constexpr const char* FILE_NAME_BIN_GRAPHICS_LAYER_STATUS = "graphics_layer_status.bin"; 

constexpr const char* FILE_NAME_BIN_MATERIAL = "material.bin"; 

constexpr const char* FILE_NAME_BIN_CONVERGENCE = "convergence.bin"; 
constexpr const char* FILE_NAME_BIN_DEFAULT = "default.bin"; 
constexpr const char* FILE_NAME_BIN_EXPLOSION = "explosion.bin"; 
constexpr const char* FILE_NAME_BIN_FIRE = "fire.bin"; 
constexpr const char* FILE_NAME_BIN_FIREWORKS = "fireworks.bin"; 
constexpr const char* FILE_NAME_BIN_RAIN = "rain.bin"; 
constexpr const char* FILE_NAME_BIN_RAIN_GROUND = "rain_ground.bin"; 
constexpr const char* FILE_NAME_BIN_SMOKE = "smoke.bin"; 
constexpr const char* FILE_NAME_BIN_SNOW = "snow.bin"; 
constexpr const char* FILE_NAME_BIN_WATER_FALL = "water_fall.bin"; 

constexpr const char* FILE_NAME_BIN_SKYBOX_MATERIAL = "skybox_material.bin"; 

constexpr const char* FILE_NAME_BIN_WATER_PLANE = "water_plane.bin"; 

constexpr const char* FILE_NAME_OTF_03TAKIBI_REGULAR = "03Takibi-Regular.otf"; 
constexpr const char* FILE_NAME_OTF_CORPORATE_LOGO_ROUNDED_BOLD_VER3 = "Corporate-Logo-Rounded-Bold-ver3.otf"; 

constexpr const char* FILE_NAME_PNG_BAR = "bar.png"; 
constexpr const char* FILE_NAME_PNG_BLACK1 = "black1.png"; 
constexpr const char* FILE_NAME_PNG_BLOCK = "block.png"; 

constexpr const char* FILE_NAME_JSON_EXAMPLE = "example.json"; 

constexpr const char* FILE_NAME_PSO_EREA_PROJECTION = "erea_projection.pso"; 
constexpr const char* FILE_NAME_VSO_EREA_PROJECTION = "erea_projection.vso"; 

constexpr const char* FILE_NAME_MP3_SE_SAMPLE_0 = "se_sample_0.mp3"; 



//------------------------------------------------------------------------------------------------------------------
// 
// file name table 
// 


const std::vector<const char*> FILE_NAME_TBL_CSV = {
    FILE_NAME_CSV_EXAMPLE,
    FILE_NAME_CSV_EXAMPLE_MAP_CHIP,
};
const std::vector<const char*> FILE_NAME_TBL_DXE_PARAMETERS_DIRECTIONAL_LIGHT = {
    FILE_NAME_BIN_DIRECTIONAL_LIGHT_PARAMETER,
};
const std::vector<const char*> FILE_NAME_TBL_DXE_PARAMETERS_GRAPHICS_LAYER = {
    FILE_NAME_BIN_GRAPHICS_LAYER_STATUS,
};
const std::vector<const char*> FILE_NAME_TBL_DXE_PARAMETERS_MESH_MATERIAL = {
    FILE_NAME_BIN_MATERIAL,
};
const std::vector<const char*> FILE_NAME_TBL_DXE_PARAMETERS_PARTICLE_PRESET = {
    FILE_NAME_BIN_CONVERGENCE,
    FILE_NAME_BIN_DEFAULT,
    FILE_NAME_BIN_EXPLOSION,
    FILE_NAME_BIN_FIRE,
    FILE_NAME_BIN_FIREWORKS,
    FILE_NAME_BIN_RAIN,
    FILE_NAME_BIN_RAIN_GROUND,
    FILE_NAME_BIN_SMOKE,
    FILE_NAME_BIN_SNOW,
    FILE_NAME_BIN_WATER_FALL,
};
const std::vector<const char*> FILE_NAME_TBL_DXE_PARAMETERS_SKYBOX_MATERIAL = {
    FILE_NAME_BIN_SKYBOX_MATERIAL,
};
const std::vector<const char*> FILE_NAME_TBL_DXE_PARAMETERS_WATER_PLANE = {
    FILE_NAME_BIN_WATER_PLANE,
};
const std::vector<const char*> FILE_NAME_TBL_FONT = {
    FILE_NAME_OTF_03TAKIBI_REGULAR,
    FILE_NAME_OTF_CORPORATE_LOGO_ROUNDED_BOLD_VER3,
};
const std::vector<const char*> FILE_NAME_TBL_GRAPHICS = {
    FILE_NAME_PNG_BAR,
    FILE_NAME_PNG_BLACK1,
    FILE_NAME_PNG_BLOCK,
};
const std::vector<const char*> FILE_NAME_TBL_JSON = {
    FILE_NAME_JSON_EXAMPLE,
};
const std::vector<const char*> FILE_NAME_TBL_SHADER_DXE = {
    FILE_NAME_PSO_EREA_PROJECTION,
    FILE_NAME_VSO_EREA_PROJECTION,
};
const std::vector<const char*> FILE_NAME_TBL_SOUND_EXAMPLE = {
    FILE_NAME_MP3_SE_SAMPLE_0,
};


//------------------------------------------------------------------------------------------------------------------
// 
// font name 
// 


constexpr const char* FONT_NAME_03TAKIBI_REGULAR = "03Takibi-Regular"; 
constexpr const char* FONT_NAME_CORPORATE_LOGO_ROUNDED_VER3 = "Corporate Logo Rounded ver3"; 


//------------------------------------------------------------------------------------------------------------------
// 
// font name table 
// 


const std::vector<const char*> FONT_NAME_TABLE = { 
     FONT_NAME_03TAKIBI_REGULAR,
     FONT_NAME_CORPORATE_LOGO_ROUNDED_VER3,
};


//------------------------------------------------------------------------------------------------------------------
// 
// font name to path map 
// 


const std::unordered_map<std::string, const char*> FONT_NAME_TO_PATH_DICTIONARY = { 
     { std::string( FONT_NAME_03TAKIBI_REGULAR ), "resource/font/03Takibi-Regular.otf" },
     { std::string( FONT_NAME_CORPORATE_LOGO_ROUNDED_VER3 ), "resource/font/Corporate-Logo-Rounded-Bold-ver3.otf" },
};

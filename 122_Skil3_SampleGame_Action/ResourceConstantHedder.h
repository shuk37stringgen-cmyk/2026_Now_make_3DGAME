#pragma once



//------------------------------------------------------------------------------------------------------------------
// 
// file path 
// 


constexpr const char* FILE_PATH_CSV_ENEMY_MOB_OCTOPUS = "resource/csv/enemy_mob_octopus.csv"; 
constexpr const char* FILE_PATH_CSV_STAGE1_FIELD_INFO = "resource/csv/stage1_field_info.csv"; 

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

constexpr const char* FILE_PATH_PNG_BLACK1 = "resource/graphics/black1.png"; 
constexpr const char* FILE_PATH_PNG_BLOCK = "resource/graphics/block.png"; 
constexpr const char* FILE_PATH_PNG_C2_ANIM_IDLE = "resource/graphics/c2_anim_idle.png"; 
constexpr const char* FILE_PATH_PNG_C2_ANIM_JUMP = "resource/graphics/c2_anim_jump.png"; 
constexpr const char* FILE_PATH_PNG_C2_ANIM_RUN = "resource/graphics/c2_anim_run.png"; 
constexpr const char* FILE_PATH_PNG_C2_ANIM_WALK = "resource/graphics/c2_anim_walk.png"; 
constexpr const char* FILE_PATH_PNG_CROUCH = "resource/graphics/crouch.png"; 
constexpr const char* FILE_PATH_PNG_ENEMY = "resource/graphics/enemy.png"; 
constexpr const char* FILE_PATH_PNG_SKY01 = "resource/graphics/sky01.png"; 
constexpr const char* FILE_PATH_PNG_STAR = "resource/graphics/star.png"; 
constexpr const char* FILE_PATH_PNG_SURPRISE = "resource/graphics/surprise.png"; 

constexpr const char* FILE_PATH_JSON_EXAMPLE = "resource/json/example.json"; 

constexpr const char* FILE_PATH_PSO_EREA_PROJECTION = "resource/shader/dxe/erea_projection.pso"; 
constexpr const char* FILE_PATH_VSO_EREA_PROJECTION = "resource/shader/dxe/erea_projection.vso"; 

constexpr const char* FILE_PATH_MP3_SE_SAMPLE_0 = "resource/sound/example/se_sample_0.mp3"; 



//------------------------------------------------------------------------------------------------------------------
// 
// file path table 
// 


const std::vector<const char*> FILE_PATH_TBL_CSV = {
    FILE_PATH_CSV_ENEMY_MOB_OCTOPUS,
    FILE_PATH_CSV_STAGE1_FIELD_INFO,
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
    FILE_PATH_PNG_BLACK1,
    FILE_PATH_PNG_BLOCK,
    FILE_PATH_PNG_C2_ANIM_IDLE,
    FILE_PATH_PNG_C2_ANIM_JUMP,
    FILE_PATH_PNG_C2_ANIM_RUN,
    FILE_PATH_PNG_C2_ANIM_WALK,
    FILE_PATH_PNG_CROUCH,
    FILE_PATH_PNG_ENEMY,
    FILE_PATH_PNG_SKY01,
    FILE_PATH_PNG_STAR,
    FILE_PATH_PNG_SURPRISE,
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
    { std::string( "enemy_mob_octopus.csv" ), FILE_PATH_CSV_ENEMY_MOB_OCTOPUS },
    { std::string( "stage1_field_info.csv" ), FILE_PATH_CSV_STAGE1_FIELD_INFO },
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
    { std::string( "black1.png" ), FILE_PATH_PNG_BLACK1 },
    { std::string( "block.png" ), FILE_PATH_PNG_BLOCK },
    { std::string( "c2_anim_idle.png" ), FILE_PATH_PNG_C2_ANIM_IDLE },
    { std::string( "c2_anim_jump.png" ), FILE_PATH_PNG_C2_ANIM_JUMP },
    { std::string( "c2_anim_run.png" ), FILE_PATH_PNG_C2_ANIM_RUN },
    { std::string( "c2_anim_walk.png" ), FILE_PATH_PNG_C2_ANIM_WALK },
    { std::string( "crouch.png" ), FILE_PATH_PNG_CROUCH },
    { std::string( "enemy.png" ), FILE_PATH_PNG_ENEMY },
    { std::string( "sky01.png" ), FILE_PATH_PNG_SKY01 },
    { std::string( "star.png" ), FILE_PATH_PNG_STAR },
    { std::string( "surprise.png" ), FILE_PATH_PNG_SURPRISE },
    { std::string( "example.json" ), FILE_PATH_JSON_EXAMPLE },
    { std::string( "erea_projection.pso" ), FILE_PATH_PSO_EREA_PROJECTION },
    { std::string( "erea_projection.vso" ), FILE_PATH_VSO_EREA_PROJECTION },
    { std::string( "se_sample_0.mp3" ), FILE_PATH_MP3_SE_SAMPLE_0 },
};


//------------------------------------------------------------------------------------------------------------------
// 
// file name 
// 


constexpr const char* FILE_NAME_CSV_ENEMY_MOB_OCTOPUS = "enemy_mob_octopus.csv"; 
constexpr const char* FILE_NAME_CSV_STAGE1_FIELD_INFO = "stage1_field_info.csv"; 

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

constexpr const char* FILE_NAME_PNG_BLACK1 = "black1.png"; 
constexpr const char* FILE_NAME_PNG_BLOCK = "block.png"; 
constexpr const char* FILE_NAME_PNG_C2_ANIM_IDLE = "c2_anim_idle.png"; 
constexpr const char* FILE_NAME_PNG_C2_ANIM_JUMP = "c2_anim_jump.png"; 
constexpr const char* FILE_NAME_PNG_C2_ANIM_RUN = "c2_anim_run.png"; 
constexpr const char* FILE_NAME_PNG_C2_ANIM_WALK = "c2_anim_walk.png"; 
constexpr const char* FILE_NAME_PNG_CROUCH = "crouch.png"; 
constexpr const char* FILE_NAME_PNG_ENEMY = "enemy.png"; 
constexpr const char* FILE_NAME_PNG_SKY01 = "sky01.png"; 
constexpr const char* FILE_NAME_PNG_STAR = "star.png"; 
constexpr const char* FILE_NAME_PNG_SURPRISE = "surprise.png"; 

constexpr const char* FILE_NAME_JSON_EXAMPLE = "example.json"; 

constexpr const char* FILE_NAME_PSO_EREA_PROJECTION = "erea_projection.pso"; 
constexpr const char* FILE_NAME_VSO_EREA_PROJECTION = "erea_projection.vso"; 

constexpr const char* FILE_NAME_MP3_SE_SAMPLE_0 = "se_sample_0.mp3"; 



//------------------------------------------------------------------------------------------------------------------
// 
// file name table 
// 


const std::vector<const char*> FILE_NAME_TBL_CSV = {
    FILE_NAME_CSV_ENEMY_MOB_OCTOPUS,
    FILE_NAME_CSV_STAGE1_FIELD_INFO,
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
    FILE_NAME_PNG_BLACK1,
    FILE_NAME_PNG_BLOCK,
    FILE_NAME_PNG_C2_ANIM_IDLE,
    FILE_NAME_PNG_C2_ANIM_JUMP,
    FILE_NAME_PNG_C2_ANIM_RUN,
    FILE_NAME_PNG_C2_ANIM_WALK,
    FILE_NAME_PNG_CROUCH,
    FILE_NAME_PNG_ENEMY,
    FILE_NAME_PNG_SKY01,
    FILE_NAME_PNG_STAR,
    FILE_NAME_PNG_SURPRISE,
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

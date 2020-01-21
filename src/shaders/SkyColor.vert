#version 330

layout(location = 0) in vec4 in_Position;

uniform SharedMatrices
{
    mat4 ViewMatrix;
    mat4 ProjectionMatrix;
};

uniform float dayTime;

out vec3 passColor;

const vec3 zenithColorDay = vec3(0.1, 0.4, 1.0);
const vec3 horizonColorDay = vec3(0.6, 0.85, 1.0);

const vec3 zenithColorNight = vec3(0.03, 0.04, 0.04);
const vec3 horizonColorNight = vec3(0.05, 0.04, 0.08);

const vec3 zenithColorSunRise = vec3(0.5, 0.4, 0.5);
const vec3 horizonColorSunRise = vec3(0.8, 0.55, 0.15);
const vec3 zenithColorMoonRise = vec3(0.4, 0.4, 0.7);
const vec3 horizonColorMoonRise = vec3(0.5, 0.45, 0.65);

vec3 getColor(float time, vec4 vertex){
    if(vertex.w == 1 || vertex.w == 2){
        if(dayTime < 37.5){ //6am - 9am sun gets brighter
            return mix(zenithColorMoonRise, zenithColorDay, dayTime / 37.5); 
        }
        if(dayTime >= 37.5 && dayTime < 112.5){ //9am - 3pm sun is brightest
            return zenithColorDay;
        }
        if(dayTime >= 112.5 && dayTime < 150.0){ //3pm - 6pm sun gets dimmer
            return mix(zenithColorDay, zenithColorSunRise, (dayTime - 112.5) / 37.5);
        }
        if(dayTime >= 150.0 && dayTime < 187.5){ //6pm - 9pm sun light fades
            return mix(zenithColorSunRise, zenithColorNight, (dayTime - 150.0)/ 37.5);
        }
        if(dayTime >= 187.5 && dayTime < 262.5){//9pm - 3am is night
            return zenithColorNight;
        }
        if(dayTime >= 262.5 && dayTime < 300){
            return mix(zenithColorNight, zenithColorMoonRise,(dayTime-262.5) / 37.5);
        }
    }else if(vertex.w == 0 || vertex.w == 3){
        if(dayTime < 37.5){ //6am - 9am sun gets brighter
            return mix(horizonColorMoonRise, horizonColorDay, dayTime / 37.5); 
        }
        if(dayTime >= 37.5 && dayTime < 112.5){ //9am - 3pm sun is brightest
            return horizonColorDay;
        }
        if(dayTime >= 112.5 && dayTime < 150.0){ //3pm - 6pm sun gets dimmer
            return mix(horizonColorDay, horizonColorSunRise, (dayTime - 112.5) / 37.5);
        }
        if(dayTime >= 150.0 && dayTime < 187.5){ //6pm - 9pm sun light fades
            return mix(horizonColorSunRise, horizonColorNight, (dayTime - 150.0)/ 37.5);
        }
        if(dayTime >= 187.5 && dayTime < 262.5){//9pm - 3am is night
            return horizonColorNight;
        }
        if(dayTime >= 262.5 && dayTime < 300){
            return mix(horizonColorNight, horizonColorMoonRise,(dayTime-262.5) / 37.5);
        }
    }else if(vertex.w == 5 || vertex.w == 6){
        if(dayTime < 37.5){ //6am - 9am sun gets brighter
            return mix(zenithColorSunRise, zenithColorDay, dayTime / 37.5); 
        }
        if(dayTime >= 37.5 && dayTime < 112.5){ //9am - 3pm sun is brightest
            return zenithColorDay;
        }
        if(dayTime >= 112.5 && dayTime < 150.0){ //3pm - 6pm sun gets dimmer
            return mix(zenithColorDay, zenithColorMoonRise, (dayTime - 112.5) / 37.5);
        }
        if(dayTime >= 150.0 && dayTime < 187.5){ //6pm - 9pm sun light fades
            return mix(zenithColorMoonRise, zenithColorNight, (dayTime - 150.0)/ 37.5);
        }
        if(dayTime >= 187.5 && dayTime < 262.5){//9pm - 3am is night
            return zenithColorNight;
        }
        if(dayTime >= 262.5 && dayTime < 300){
            return mix(zenithColorNight, zenithColorSunRise,(dayTime-262.5) / 37.5);
        }
    }else if(vertex.w == 4 || vertex.w == 7){
        if(dayTime < 37.5){ //6am - 9am sun gets brighter
            return mix(horizonColorSunRise, horizonColorDay, dayTime / 37.5); 
        }
        if(dayTime >= 37.5 && dayTime < 112.5){ //9am - 3pm sun is brightest
            return horizonColorDay;
        }
        if(dayTime >= 112.5 && dayTime < 150.0){ //3pm - 6pm sun gets dimmer
            return mix(horizonColorDay, horizonColorMoonRise, (dayTime - 112.5) / 37.5);
        }
        if(dayTime >= 150.0 && dayTime < 187.5){ //6pm - 9pm sun light fades
            return mix(horizonColorMoonRise, horizonColorNight, (dayTime - 150.0)/ 37.5);
        }
        if(dayTime >= 187.5 && dayTime < 262.5){//9pm - 3am is night
            return horizonColorNight;
        }
        if(dayTime >= 262.5 && dayTime < 300){
            return mix(horizonColorNight, horizonColorSunRise,(dayTime-262.5) / 37.5);
        }
    }
}

void main(){
    gl_Position = ProjectionMatrix * ViewMatrix * vec4(in_Position.xyz, 1.0);
    passColor = getColor(dayTime, in_Position);
}
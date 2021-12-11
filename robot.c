#include "robot.h"
#include <time.h>
#include <stdio.h>
#include<stdbool.h>

//open error windows: F2

void setup_robot(struct Robot *robot){//ORIGINAL MAZE
    robot->x = OVERALL_WINDOW_WIDTH/2-50;
    robot->y = OVERALL_WINDOW_HEIGHT-50;
    robot->true_x = OVERALL_WINDOW_WIDTH/2-50;
    robot->true_y = OVERALL_WINDOW_HEIGHT-50;
    robot->width = ROBOT_WIDTH;
    robot->height = ROBOT_HEIGHT;
    robot->direction = 0;
    robot->angle = 0;
    robot->currentSpeed = 0;
    robot->crashed = 0;
    robot->auto_mode = 0;

    printf("Press arrow keys to move manually, or enter to move automatically\n\n");
}
/*
void setup_robot(struct Robot *robot){//MAZE-1
    robot->x = 270;
    robot->y = 460;
    robot->true_x = 270;
    robot->true_y = 460;
    robot->width = ROBOT_WIDTH;
    robot->height = ROBOT_HEIGHT;
    robot->direction = 0;
    robot->angle = 0;
    robot->currentSpeed = 0;
    robot->crashed = 0;
    robot->auto_mode = 0;

    printf("Press arrow keys to move manually, or enter to move automatically\n\n");
}*/
/*
void setup_robot(struct Robot *robot){//MAZE-2
    robot->x = 620;
    robot->y = 380;
    robot->true_x = 620;
    robot->true_y = 380;
    robot->width = ROBOT_WIDTH;
    robot->height = ROBOT_HEIGHT;
    robot->direction = 0;
    robot->angle = 270;
    robot->currentSpeed = 0;
    robot->crashed = 0;
    robot->auto_mode = 0;

    printf("Press arrow keys to move manually, or enter to move automatically\n\n");
}*/
/*
void setup_robot(struct Robot *robot){//MAZE-3
    robot->x = 640-10-270;
    robot->y = 460;
    robot->true_x = 640-10-270;
    robot->true_y = 460;
    robot->width = ROBOT_WIDTH;
    robot->height = ROBOT_HEIGHT;
    robot->direction = 0;
    robot->angle = 0;
    robot->currentSpeed = 0;
    robot->crashed = 0;
    robot->auto_mode = 0;

    printf("Press arrow keys to move manually, or enter to move automatically\n\n");
}*/
/*
void setup_robot(struct Robot *robot){//MAZE-4
    robot->x = 0;
    robot->y = 380;
    robot->true_x = 0;
    robot->true_y = 380;
    robot->width = ROBOT_WIDTH;
    robot->height = ROBOT_HEIGHT;
    robot->direction = 0;
    robot->angle = 90;
    robot->currentSpeed = 0;
    robot->crashed = 0;
    robot->auto_mode = 0;

    printf("Press arrow keys to move manually, or enter to move automatically\n\n");
}*/

/*
void setup_robot(struct Robot *robot){//MAZE-5
    robot->x = 170;
    robot->y = 460;
    robot->true_x = 170;
    robot->true_y = 460;
    robot->width = ROBOT_WIDTH;
    robot->height = ROBOT_HEIGHT;
    robot->direction = 0;
    robot->angle = 0;
    robot->currentSpeed = 0;
    robot->crashed = 0;
    robot->auto_mode = 0;

    printf("Press arrow keys to move manually, or enter to move automatically\n\n");
}*/
/*
void setup_robot(struct Robot *robot){//MAZE-6
    robot->x = 620;
    robot->y = 40;
    robot->true_x = 620;
    robot->true_y = 40;
    robot->width = ROBOT_WIDTH;
    robot->height = ROBOT_HEIGHT;
    robot->direction = 0;
    robot->angle = 270;
    robot->currentSpeed = 0;
    robot->crashed = 0;
    robot->auto_mode = 0;

    printf("Press arrow keys to move manually, or enter to move automatically\n\n");
}*/
/*
void setup_robot(struct Robot *robot){//MAZE-7
    robot->x = 640-10-170;
    robot->y = 460;
    robot->true_x = 640-10-170;
    robot->true_y = 460;
    robot->width = ROBOT_WIDTH;
    robot->height = ROBOT_HEIGHT;
    robot->direction = 0;
    robot->angle = 0;
    robot->currentSpeed = 0;
    robot->crashed = 0;
    robot->auto_mode = 0;

    printf("Press arrow keys to move manually, or enter to move automatically\n\n");
}*/

/*
void setup_robot(struct Robot *robot){//Maze 8
    robot->x = 0;
    robot->y = 40;
    robot->true_x = 0;
    robot->true_y = 40;
    robot->width = ROBOT_WIDTH;
    robot->height = ROBOT_HEIGHT;
    robot->direction = 0;
    robot->angle = 90;
    robot->currentSpeed = 0;
    robot->crashed = 0;
    robot->auto_mode = 0;

    printf("Press arrow keys to move manually, or enter to move automatically\n\n");
}*/


int robot_off_screen(struct Robot * robot){
    if(robot->x < 0 || robot-> y < 0){
        return 0;
    }
    if(robot->x > OVERALL_WINDOW_WIDTH || robot->y > OVERALL_WINDOW_HEIGHT){
        return 0;
    }
    return 1;
}

int checkRobotHitWall(struct Robot * robot, struct Wall * wall) {

    int overlap = checkOverlap(robot->x,robot->width,robot->y,robot->height,
                 wall->x,wall->width,wall->y, wall->height);

    return overlap;
}

int checkRobotHitWalls(struct Robot * robot, struct Wall_collection * head) {
   struct Wall_collection *ptr = head;
   int hit = 0;

   while(ptr != NULL) {
      hit = (hit || checkRobotHitWall(robot, &ptr->wall));
      ptr = ptr->next;
   }
   return hit;
}

int checkRobotReachedEnd(struct Robot * robot, int x, int y, int width, int height){

    int overlap = checkOverlap(robot->x,robot->width,robot->y,robot->height,
                 x,width,y,height);
    return overlap;
}

void robotCrash(struct Robot * robot) {
    robot->currentSpeed = 0;
    if (!robot->crashed)
        printf("Ouchies!!!!!\n\nPress space to start again\n");
    robot->crashed = 1;
}

void robotSuccess(struct Robot * robot, int msec) {
    robot->currentSpeed = 0;
    if (!robot->crashed){
        printf("Success!!!!!\n\n");
        printf("Time taken %d seconds %d milliseconds \n", msec/1000, msec%1000);
        printf("Press space to start again\n");
    }
    robot->crashed = 1;
}

int checkRobotSensor(int x, int y, int sensorSensitivityLength, struct Wall * wall)  {
    //viewing_region of sensor is a square of 2 pixels * chosen length of sensitivity
    int overlap = checkOverlap(x,2,y,sensorSensitivityLength,
                 wall->x,wall->width,wall->y, wall->height);

    return overlap;
}

int checkRobotSensorFrontRightAllWalls(struct Robot * robot, struct Wall_collection * head) {
    struct Wall_collection *ptr, *head_store;
    int i;
    double xDir, yDir;
    int robotCentreX, robotCentreY, xTL, yTL;
    int score, hit;

    int sensorSensitivityLength =  floor(SENSOR_VISION/5);

    head_store = head;
    robotCentreX = robot->x+ROBOT_WIDTH/2;
    robotCentreY = robot->y+ROBOT_HEIGHT/2;
    score = 0;

    for (i = 0; i < 5; i++)
    {
        ptr = head_store;
        xDir = round(robotCentreX+(ROBOT_WIDTH/2-2)*cos((robot->angle)*PI/180)-(-ROBOT_HEIGHT/2-SENSOR_VISION+sensorSensitivityLength*i)*sin((robot->angle)*PI/180));
        yDir = round(robotCentreY+(ROBOT_WIDTH/2-2)*sin((robot->angle)*PI/180)+(-ROBOT_HEIGHT/2-SENSOR_VISION+sensorSensitivityLength*i)*cos((robot->angle)*PI/180));
        xTL = (int) xDir;
        yTL = (int) yDir;
        hit = 0;

        while(ptr != NULL) {
            hit = (hit || checkRobotSensor(xTL, yTL, sensorSensitivityLength, &ptr->wall));
            ptr = ptr->next;
        }
        if (hit)
            score = i;
    }
    return score;
}

int checkRobotSensorFrontLeftAllWalls(struct Robot * robot, struct Wall_collection * head) {
    struct Wall_collection *ptr, *head_store;
    int i;
    double xDir, yDir;
    int robotCentreX, robotCentreY, xTL, yTL;
    int score, hit;
    int sensorSensitivityLength;

    head_store = head;
    robotCentreX = robot->x+ROBOT_WIDTH/2;
    robotCentreY = robot->y+ROBOT_HEIGHT/2;
    score = 0;
    sensorSensitivityLength =  floor(SENSOR_VISION/5);

    for (i = 0; i < 5; i++)
    {
        ptr = head_store;
        xDir = round(robotCentreX+(-ROBOT_WIDTH/2)*cos((robot->angle)*PI/180)-(-ROBOT_HEIGHT/2-SENSOR_VISION+sensorSensitivityLength*i)*sin((robot->angle)*PI/180));
        yDir = round(robotCentreY+(-ROBOT_WIDTH/2)*sin((robot->angle)*PI/180)+(-ROBOT_HEIGHT/2-SENSOR_VISION+sensorSensitivityLength*i)*cos((robot->angle)*PI/180));
        xTL = (int) xDir;
        yTL = (int) yDir;
        hit = 0;

        while(ptr != NULL) {
            hit = (hit || checkRobotSensor(xTL, yTL, sensorSensitivityLength, &ptr->wall));
            ptr = ptr->next;
        }
        if (hit)
            score = i;
    }
    return score;
}

void robotUpdate(struct SDL_Renderer * renderer, struct Robot * robot){
    double xDir, yDir;

    int robotCentreX, robotCentreY, xTR, yTR, xTL, yTL, xBR, yBR, xBL, yBL;
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);

    /*
    //Other Display options:
    // The actual square which the robot is tested against (not so nice visually with turns, but easier
    // to test overlap
    SDL_Rect rect = {robot->x, robot->y, robot->height, robot->width};
    SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);
    SDL_RenderDrawRect(renderer, &rect);
    SDL_RenderFillRect(renderer, &rect);
    */
    /*
    //Center Line of Robot. Line shows the direction robot is facing
    xDir = -30 * sin(-robot->angle*PI/180);
    yDir = -30 * cos(-robot->angle*PI/180);
    xDirInt = robot->x+ROBOT_WIDTH/2+ (int) xDir;
    yDirInt = robot->y+ROBOT_HEIGHT/2+ (int) yDir;
    SDL_RenderDrawLine(renderer,robot->x+ROBOT_WIDTH/2, robot->y+ROBOT_HEIGHT/2, xDirInt, yDirInt);
    */

    //Rotating Square
    //Vector rotation to work out corners x2 = x1cos(angle)-y1sin(angle), y2 = x1sin(angle)+y1cos(angle)
    robotCentreX = robot->x+ROBOT_WIDTH/2;
    robotCentreY = robot->y+ROBOT_HEIGHT/2;

    xDir = round(robotCentreX+(ROBOT_WIDTH/2)*cos((robot->angle)*PI/180)-(-ROBOT_HEIGHT/2)*sin((robot->angle)*PI/180));
    yDir = round(robotCentreY+(ROBOT_WIDTH/2)*sin((robot->angle)*PI/180)+(-ROBOT_HEIGHT/2)*cos((robot->angle)*PI/180));
    xTR = (int) xDir;
    yTR = (int) yDir;

    xDir = round(robotCentreX+(ROBOT_WIDTH/2)*cos((robot->angle)*PI/180)-(ROBOT_HEIGHT/2)*sin((robot->angle)*PI/180));
    yDir = round(robotCentreY+(ROBOT_WIDTH/2)*sin((robot->angle)*PI/180)+(ROBOT_HEIGHT/2)*cos((robot->angle)*PI/180));
    xBR = (int) xDir;
    yBR = (int) yDir;

    xDir = round(robotCentreX+(-ROBOT_WIDTH/2)*cos((robot->angle)*PI/180)-(ROBOT_HEIGHT/2)*sin((robot->angle)*PI/180));
    yDir = round(robotCentreY+(-ROBOT_WIDTH/2)*sin((robot->angle)*PI/180)+(ROBOT_HEIGHT/2)*cos((robot->angle)*PI/180));
    xBL = (int) xDir;
    yBL = (int) yDir;

    xDir = round(robotCentreX+(-ROBOT_WIDTH/2)*cos((robot->angle)*PI/180)-(-ROBOT_HEIGHT/2)*sin((robot->angle)*PI/180));
    yDir = round(robotCentreY+(-ROBOT_WIDTH/2)*sin((robot->angle)*PI/180)+(-ROBOT_HEIGHT/2)*cos((robot->angle)*PI/180));
    xTL = (int) xDir;
    yTL = (int) yDir;

    SDL_RenderDrawLine(renderer,xTR, yTR, xBR, yBR);
    SDL_RenderDrawLine(renderer,xBR, yBR, xBL, yBL);
    SDL_RenderDrawLine(renderer,xBL, yBL, xTL, yTL);
    SDL_RenderDrawLine(renderer,xTL, yTL, xTR, yTR);

    //Front Right Sensor
    int sensor_sensitivity =  floor(SENSOR_VISION/5);
    int i;
    for (i = 0; i < 5; i++)
    {
        xDir = round(robotCentreX+(ROBOT_WIDTH/2-2)*cos((robot->angle)*PI/180)-(-ROBOT_HEIGHT/2-SENSOR_VISION+sensor_sensitivity*i)*sin((robot->angle)*PI/180));
        yDir = round(robotCentreY+(ROBOT_WIDTH/2-2)*sin((robot->angle)*PI/180)+(-ROBOT_HEIGHT/2-SENSOR_VISION+sensor_sensitivity*i)*cos((robot->angle)*PI/180));

        xTL = (int) xDir;
        yTL = (int) yDir;

        SDL_Rect rect = {xTL, yTL, 2, sensor_sensitivity};
        SDL_SetRenderDrawColor(renderer, 80+(20*(5-i)), 80+(20*(5-i)), 80+(20*(5-i)), 255);
        SDL_RenderDrawRect(renderer, &rect);
        SDL_RenderFillRect(renderer, &rect);
    }

    //Front Left Sensor
    for (i = 0; i < 5; i++)
    {
        xDir = round(robotCentreX+(-ROBOT_WIDTH/2)*cos((robot->angle)*PI/180)-(-ROBOT_HEIGHT/2-SENSOR_VISION+sensor_sensitivity*i)*sin((robot->angle)*PI/180));
        yDir = round(robotCentreY+(-ROBOT_WIDTH/2)*sin((robot->angle)*PI/180)+(-ROBOT_HEIGHT/2-SENSOR_VISION+sensor_sensitivity*i)*cos((robot->angle)*PI/180));

        xTL = (int) xDir;
        yTL = (int) yDir;

        SDL_Rect rect = {xTL, yTL, 2, sensor_sensitivity};
        SDL_SetRenderDrawColor(renderer, 80+(20*(5-i)), 80+(20*(5-i)), 80+(20*(5-i)), 255);
        SDL_RenderDrawRect(renderer, &rect);
        SDL_RenderFillRect(renderer, &rect);
    }
    //Side Right Sensor
    for (i = 0; i < 5; i++)
    {
        xDir = round( (robotCentreX) + ((-ROBOT_WIDTH/4)*cos((robot->angle)*PI/180)) + ((-ROBOT_HEIGHT/2-SENSOR_VISION+sensor_sensitivity*i)*-cos((robot->angle)*PI/180)));
        yDir = round( (robotCentreY) + ((-ROBOT_WIDTH/4)*sin((robot->angle)*PI/180)) - ((-ROBOT_HEIGHT/2-SENSOR_VISION+sensor_sensitivity*i)*sin((robot->angle)*PI/180)));

        xTL = (int) xDir;
        yTL = (int) yDir;

        SDL_Rect rect = {xTL, yTL, 2, sensor_sensitivity};
        SDL_SetRenderDrawColor(renderer, 80+(20*(5-i)), 80+(20*(5-i)), 80+(20*(5-i)), 255);
        SDL_RenderDrawRect(renderer, &rect);
        SDL_RenderFillRect(renderer, &rect);
    }

    //Side Left Sensor
    for (i = 0; i < 5; i++)
    {


        xDir = round( (robotCentreX) + ((ROBOT_WIDTH/4)*cos((robot->angle)*PI/180)) - ((-ROBOT_HEIGHT/2-SENSOR_VISION+sensor_sensitivity*i)*-cos((robot->angle)*PI/180)));
        yDir = round( (robotCentreY) + ((ROBOT_WIDTH/4)*sin((robot->angle)*PI/180)) + ((-ROBOT_HEIGHT/2-SENSOR_VISION+sensor_sensitivity*i)*sin((robot->angle)*PI/180)));



        xTL = (int) xDir;
        yTL = (int) yDir;

        SDL_Rect rect = {xTL, yTL, 2, sensor_sensitivity};
        SDL_SetRenderDrawColor(renderer, 80+(20*(5-i)), 80+(20*(5-i)), 80+(20*(5-i)), 255);
        SDL_RenderDrawRect(renderer, &rect);
        SDL_RenderFillRect(renderer, &rect);
    }
}

int rightSensor(struct Robot * robot, struct Wall_collection * head) {
    struct Wall_collection *ptr, *head_store;
    int i;
    double xDir, yDir;
    int robotCentreX, robotCentreY, xTL, yTL;
    int score, hit;
    int sensorSensitivityLength;

    head_store = head;
    robotCentreX = robot->x+ROBOT_WIDTH/2;
    robotCentreY = robot->y+ROBOT_HEIGHT/2;
    score = 0;
    sensorSensitivityLength =  floor(SENSOR_VISION/5);

    for (i = 0; i < 5; i++)
    {
        ptr = head_store;
        xDir = round( (robotCentreX) + ((-ROBOT_WIDTH/4)*cos((robot->angle)*PI/180)) + ((-ROBOT_HEIGHT/2-SENSOR_VISION+sensorSensitivityLength*i)*-cos((robot->angle)*PI/180)));
        yDir = round( (robotCentreY) + ((-ROBOT_WIDTH/4)*sin((robot->angle)*PI/180)) - ((-ROBOT_HEIGHT/2-SENSOR_VISION+sensorSensitivityLength*i)*sin((robot->angle)*PI/180)));

        xTL = (int) xDir;
        yTL = (int) yDir;
        hit = 0;

        while(ptr != NULL) {
            hit = (hit || checkRobotSensor(xTL, yTL, sensorSensitivityLength, &ptr->wall));
            ptr = ptr->next;
        }
        if (hit)
            score = i;
    }
    return score;
}

int leftSensor(struct Robot * robot, struct Wall_collection * head) {
    struct Wall_collection *ptr, *head_store;
    int i;
    double xDir, yDir;
    int robotCentreX, robotCentreY, xTL, yTL;
    int score, hit;
    int sensorSensitivityLength;

    head_store = head;
    robotCentreX = robot->x+ROBOT_WIDTH/2;
    robotCentreY = robot->y+ROBOT_HEIGHT/2;
    score = 0;
    sensorSensitivityLength =  floor(SENSOR_VISION/5);

    for (i = 0; i < 5; i++)
    {
        ptr = head_store;
        xDir = round( (robotCentreX) + ((ROBOT_WIDTH/4)*cos((robot->angle)*PI/180)) - ((-ROBOT_HEIGHT/2-SENSOR_VISION+sensorSensitivityLength*i)*-cos((robot->angle)*PI/180)));
        yDir = round( (robotCentreY) + ((ROBOT_WIDTH/4)*sin((robot->angle)*PI/180)) + ((-ROBOT_HEIGHT/2-SENSOR_VISION+sensorSensitivityLength*i)*sin((robot->angle)*PI/180)));

        xTL = (int) xDir;
        yTL = (int) yDir;
        hit = 0;

        while(ptr != NULL) {
            hit = (hit || checkRobotSensor(xTL, yTL, sensorSensitivityLength, &ptr->wall));
            ptr = ptr->next;
        }
        if (hit)
            score = i;
    }
    return score;
}


void robotMotorMove(struct Robot * robot) {
    double x_offset, y_offset;
    switch(robot->direction){
        case UP :
            robot->currentSpeed += DEFAULT_SPEED_CHANGE;
            if (robot->currentSpeed > MAX_ROBOT_SPEED)
                robot->currentSpeed = MAX_ROBOT_SPEED;
            break;
        case DOWN :
            robot->currentSpeed -= DEFAULT_SPEED_CHANGE;
            if (robot->currentSpeed < -MAX_ROBOT_SPEED)
                robot->currentSpeed = -MAX_ROBOT_SPEED;
            break;
        case LEFT :
            robot->angle = (robot->angle+360-DEFAULT_ANGLE_CHANGE)%360;
            break;
        case RIGHT :
            robot->angle = (robot->angle+DEFAULT_ANGLE_CHANGE)%360;
            break;
    }
    robot->direction = 0;
    x_offset = (-robot->currentSpeed * sin(-robot->angle*PI/180));
    y_offset = (-robot->currentSpeed * cos(-robot->angle*PI/180));

    robot->true_x += x_offset;
    robot->true_y += y_offset;

    x_offset = round(robot->true_x);
    y_offset = round(robot->true_y);

    robot->x = (int) x_offset;
    robot->y = (int) y_offset;
}

void robotAutoMotorMove(struct Robot * robot, int front_left_sensor, int front_right_sensor) {

    if ((front_left_sensor == 0) && (front_right_sensor == 0)) {
        if (robot->currentSpeed<2)
            robot->currentSpeed = 1;
            robot->direction = UP;
    }
    else if ((robot->currentSpeed>0) && ((front_left_sensor == 1) || (front_right_sensor == 1)) ) {
        robot->direction = DOWN;
    }
    else if ((robot->currentSpeed==0) && ((front_left_sensor == 1) || (front_right_sensor == 1)) ) {
        robot->direction = LEFT;
    }
    else if ((robot->currentSpeed==0) && ((front_left_sensor == 1) || (front_right_sensor == 0)) ) {
        robot->direction = RIGHT;
    }
    else if ((robot->currentSpeed==0) && ((front_left_sensor == 0) || (front_right_sensor == 1)) ) {
        robot->direction = RIGHT;
    }
}

void nudge(struct Robot * robot) {
    //if the robot is in a loop, nudge it out
    robot->direction = UP;
    //don't speed up too much to lose control
    if (robot->currentSpeed > 4) {
        robot->currentSpeed--;
    }
}

int wallFinderN(struct Robot * robot, int front_left_sensor, int front_right_sensor, int right_sensor, int left_sensor) {
//REAL NAVIGATOR

    //used as a breaker
    bool flag = true;

    if (robot->currentSpeed < 2 ) {//set speed here
        //robot->currentSpeed++;
        //robot->direction = UP;
        printf("sped up\n");

    } else if (flag && front_left_sensor == 0 && front_right_sensor  == 0 && right_sensor > 0) {
        //front clear, wall right
        //keep on, UP speeds up too much
        flag = false;
        printf("1\n");
        return 1;
    } else if (flag && front_left_sensor == front_right_sensor && front_left_sensor > 0 && left_sensor > 0) {
        //front blocked, wall left
        robot->direction = LEFT;
        flag = false;
        printf("2\n");
        return 2;
    } else if (flag && front_left_sensor == 0 && front_right_sensor == 0 && right_sensor > 0) {
        //front clear, wall right
        robot->direction = RIGHT;
        flag = false;
        printf("3\n");
        return 3;
    } else if (flag && front_left_sensor == 0 && front_right_sensor == 0 && left_sensor == 0 && right_sensor == 0) {
        //front clear, walls clear
        robot->direction = RIGHT;
        flag = false;
        printf("4\n");
        return 4;
    } else if (flag && front_right_sensor > front_left_sensor && right_sensor == 0 && right_sensor == 0) {
        //front blocked, walls clear, angled right
        robot->direction = LEFT;
        flag = false;
        printf("5\n");
        return 5;
    } else if (flag && front_right_sensor > 0 && right_sensor > 0 && right_sensor < 3 && left_sensor == 0 && front_left_sensor > 0) {
        //front blocked, wall right
        robot->direction = LEFT;
        flag = false;
        printf("6\n");
        return 6;
    } else if (flag && front_left_sensor > 0 && left_sensor > 0 && right_sensor == 0 && front_right_sensor > 0) {
        //front blocked, wall left
        robot->direction == RIGHT;
        flag = false;
        printf("7\n");
        return 7;
    } else if (flag && front_left_sensor > 0 && front_right_sensor > 0 && right_sensor > 0 && left_sensor > 0 ) {
        //front blocked, walls sides
        robot->direction = DOWN;
        flag = false;
        printf("8\n");
        return 8;
    } else if (flag && front_left_sensor == 0 && front_right_sensor == 0 && right_sensor > 0 && left_sensor > 0) {
        //front clear, walls sides
        //robot->direction = UP;
        flag = false;
        printf("9\n");
        return 9;
    } else if (flag && front_left_sensor > front_right_sensor && front_right_sensor > 0 && right_sensor > 0) {
        robot->direction = LEFT;
        flag = false;
        printf("10\n");
        return 10;
    } else if (flag && front_left_sensor > 0 && left_sensor == 0 && right_sensor == 0 && front_right_sensor == 0){
        //wall front left angled, nothing else
        robot->direction = RIGHT;
        flag = false;
        printf("11\n");
        return 11;
    } else if (flag && front_left_sensor > 0 && front_right_sensor > 0 && right_sensor == 0 && left_sensor == 0) {
        //front blocked straight on, walls clear
        robot->direction = LEFT;
        flag = false;
        printf("12\n");
        return 12;
    } else if (flag && front_left_sensor == 0 && front_right_sensor == 0 && left_sensor == 0 && right_sensor > 2) {
        //right side blocked, very close
        robot->direction = LEFT;
        flag = false;
        printf("13\n");
        return 13;
    }
}

void deloop(struct Robot * robot, int front_left_sensor, int front_right_sensor, int right_sensor, int left_sensor) {

    //if any of the sensors catch a wall

}


void wallFinder(struct Robot * robot, int front_left_sensor, int front_right_sensor, int right_sensor, int left_sensor, int sX, int sY) {
//REAL NAVIGATOR

    bool flag = true;

    if (robot->currentSpeed < 3 ) {//set speed here
        //robot->direction = UP;
        //printf("sped up\n");

    } else if (flag && front_left_sensor == 0 && front_right_sensor  == 0 && right_sensor > 0) {
        //front clear, wall right
        //keep on, UP speeds up too much
        flag = false;
        printf("1\n");
    } else if (flag && front_left_sensor == front_right_sensor && front_left_sensor > 0 && left_sensor > 0) {
        //front blocked, wall left
        robot->direction = LEFT;
        flag = false;
        printf("2\n");
    } else if (flag && front_left_sensor == 0 && front_right_sensor == 0 && right_sensor > 0) {
        //front clear, wall right
        robot->direction = RIGHT;
        flag = false;
        printf("3\n");
    } else if (flag && front_left_sensor == 0 && front_right_sensor == 0 && left_sensor == 0 && right_sensor == 0) {
        //front clear, walls clear
        robot->direction = RIGHT;
        flag = false;
        printf("4\n");
    } else if (flag && front_right_sensor > front_left_sensor && right_sensor == 0 && right_sensor == 0) {
        //front blocked, walls clear, angled right
        robot->direction = LEFT;
        flag = false;
        printf("5\n");
    } else if (flag && front_right_sensor > 0 && right_sensor > 0 && left_sensor == 0 && front_left_sensor > 0) {
        //front blocked, wall right
        robot->direction = LEFT;
        flag = false;
        printf("6\n");
    } else if (flag && front_left_sensor > 0 && left_sensor > 0 && right_sensor == 0 && front_right_sensor > 0) {
        //front blocked, wall left
        robot->direction == RIGHT;
        flag = false;
        printf("7\n");
    } else if (flag && front_left_sensor > 0 && front_right_sensor > 0 && right_sensor > 0 && left_sensor > 0 ) {
        //front blocked, walls sides
        robot->direction = DOWN;
        flag = false;
        printf("8\n");
    } else if (flag && front_left_sensor == 0 && front_right_sensor == 0 && right_sensor > 0 && left_sensor > 0) {
        //front clear, walls sides
        //robot->direction = UP;
        flag = false;
        printf("9\n");
    } else if (flag && front_left_sensor > front_right_sensor && front_right_sensor > 0 && right_sensor > 0) {
        robot->direction = LEFT;
        flag = false;
        printf("10\n");
    } else if (flag && front_left_sensor > 0 && left_sensor == 0 && right_sensor == 0 && front_right_sensor == 0){
        //wall front left angled, nothing else
        robot->direction = RIGHT;
        flag = false;
        printf("11\n");
    }
}





//these are bust
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------


void navigator(struct Robot * robot, int front_left_sensor, int front_right_sensor, int right_sensor, int left_sensor) {
    //map out each possible corner

    if ((front_left_sensor == 0 && front_right_sensor == 0) && left_sensor > 0) {
        //clear run straight plus a wall left
        //robot->currentSpeed = MAX_ROBOT_SPEED;
    } else if (front_left_sensor == 0 && left_sensor == 0) {
        //open space ahead and left, turn left
        robot->direction = LEFT;
        robot->direction = UP;

    } else if (front_left_sensor > 0 && left_sensor > 0) {
        //something ahead and to the left, turn right to hold wall
        robot->direction = RIGHT;
    } else if (front_left_sensor > 0 && left_sensor == 0) {
        //wall ahead and open left, turn left
        //shouldn't get to this one
        robot->direction = LEFT;
    } else if (front_left_sensor > 0 && left_sensor > 0 && right_sensor > 0 ) {
        //dead end, turn around
        robot->angle += 180;
    } else if (true) {
        //angled right towards wall
    }

}

void originalMaze(struct Robot * robot, int front_left_sensor, int front_right_sensor, int left_sensor, int right_sensor) {

    if (front_left_sensor == 0 && front_right_sensor == 0 && left_sensor == 0 && right_sensor == 0 ) {

        if (left_sensor == 0 ) {
            robot->direction = LEFT;
            robot->currentSpeed = 2;
            robot->direction = UP;
            printf("starting process");

        }
    }

    if ((front_left_sensor == 0) && (front_right_sensor == 0)) {
        //clear ahead
        if (robot->currentSpeed<2) {
            robot->direction = LEFT;
            robot->direction = UP;
        }
    } else if (front_left_sensor > 0 && front_right_sensor > 0 && left_sensor > 0 && right_sensor > 0) {
        //dead end
        robot->angle -= 180;
        robot->direction = UP;
    } else if (left_sensor > 0 && front_left_sensor == 0) {
        //wall left and clear ahead
        robot->direction = UP;
    } else if (left_sensor > 0 && front_left_sensor > 0) {
        //wall left and angled towards it
        robot->direction = RIGHT;
    } else if (right_sensor > 0 && front_right_sensor == 0) {
        //wall right and clear ahead
        robot->direction = RIGHT;
    } else if (right_sensor > 0 && front_right_sensor > 0) {
        //wall right and angled towards
        robot->direction = LEFT;
    } else if ((front_left_sensor > 0) && front_right_sensor > 0 && left_sensor > 0) {
        //wall ahead and left, turn right
        robot->direction = RIGHT;
    } else if (front_left_sensor > 0 && front_right_sensor > 0 && right_sensor > 0) {
        //wall ahead and right, turn left
        robot->direction = LEFT;
    } else if (front_left_sensor > 0 && front_right_sensor > 0 && left_sensor == 0 && right_sensor == 0) {
        //wall ahead and nothing either side
        robot->direction = LEFT;
    }

}

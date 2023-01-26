#include "main.h"
#include "gui.hpp"
#include "variables.hpp"
#include "display/lv_core/lv_obj.h"




//Creates Button Variables
lv_obj_t * redCloseButton;
lv_obj_t * redFarButton;
lv_obj_t * blueCloseButton;
lv_obj_t * blueFarButton;
lv_obj_t * skillsButton;
lv_obj_t * redCloseButtonLabel;
lv_obj_t * redFarButtonLabel;
lv_obj_t * blueCloseButtonLabel;
lv_obj_t * blueFarButtonLabel;
lv_obj_t * skillsButtonLabel;
lv_obj_t * selectionLabel;


//Creates Style Variables
lv_style_t redButtonStyleREL;
lv_style_t redButtonStylePR;
lv_style_t blueButtonStyleREL;
lv_style_t blueButtonStylePR;
lv_style_t skillsButtonStyleREL;
lv_style_t skillsButtonStylePR;
lv_style_t selectionLabelStyle;


//Creates Label Style
lv_style_t labelStyle;



//function for button press event 
static lv_res_t btn_click_action(lv_obj_t * btn) {
    uint8_t id = lv_obj_get_free_num(btn);

    if(id == 1) {
        autonID = 1;
        lv_label_set_text(selectionLabel, "Red Close Side Auton Selected");
    }
    if(id == 2) {
        autonID = 2;
        lv_label_set_text(selectionLabel, "Red Far Side Auton Selected");
    }
    if(id == 3) {
        autonID = 3;
        lv_label_set_text(selectionLabel, "Blue Close Side Auton Selected");
    }
    if(id == 4) {
        autonID = 4;
        lv_label_set_text(selectionLabel, "Blue Far Side Auton Selected");
    }
    if(id == 5) {
        autonID = 5;
        lv_label_set_text(selectionLabel, "Skills Auton Selected");
    }
    return LV_RES_OK;
}





void createButtons(){
    //Creates Button And Labels

//Creates Red Button Release Style
lv_style_copy(&redButtonStyleREL, &lv_style_plain);
redButtonStyleREL.body.main_color = LV_COLOR_RED;
redButtonStyleREL.body.grad_color = LV_COLOR_RED;
redButtonStyleREL.body.radius = 0;
redButtonStyleREL.body.border.color = LV_COLOR_BLACK;
redButtonStyleREL.body.border.width = 2;
redButtonStyleREL.body.border.opa = LV_OPA_50;
redButtonStyleREL.body.opa = LV_OPA_COVER;
redButtonStyleREL.text.color = LV_COLOR_WHITE;

//Creates Red Button Press Style
lv_style_copy(&redButtonStylePR, &lv_style_plain);
redButtonStylePR.body.main_color = LV_COLOR_MAROON;
redButtonStylePR.body.grad_color = LV_COLOR_MAROON;
redButtonStylePR.body.radius = 0;
redButtonStylePR.body.border.color = LV_COLOR_BLACK;
redButtonStylePR.body.border.width = 2;
redButtonStylePR.body.border.opa = LV_OPA_50;
redButtonStylePR.body.opa = LV_OPA_COVER;
redButtonStylePR.text.color = LV_COLOR_WHITE;

//Creates Blue Button Release Style
lv_style_copy(&blueButtonStyleREL, &lv_style_plain);
blueButtonStyleREL.body.main_color = LV_COLOR_BLUE;
blueButtonStyleREL.body.grad_color = LV_COLOR_BLUE;
blueButtonStyleREL.body.radius = 0;
blueButtonStyleREL.body.border.color = LV_COLOR_BLACK;
blueButtonStyleREL.body.border.width = 2;
blueButtonStyleREL.body.border.opa = LV_OPA_50;
blueButtonStyleREL.body.opa = LV_OPA_COVER;
blueButtonStyleREL.text.color = LV_COLOR_WHITE;

//Creates Blue Button Press Style
lv_style_copy(&blueButtonStylePR, &lv_style_plain);
blueButtonStylePR.body.main_color = LV_COLOR_NAVY;
blueButtonStylePR.body.grad_color = LV_COLOR_NAVY;
blueButtonStylePR.body.radius = 0;
blueButtonStylePR.body.border.color = LV_COLOR_BLACK;
blueButtonStylePR.body.border.width = 2;
blueButtonStylePR.body.border.opa = LV_OPA_50;
blueButtonStylePR.body.opa = LV_OPA_COVER;
blueButtonStylePR.text.color = LV_COLOR_WHITE;

//Creates Skills Button Release Style
lv_style_copy(&skillsButtonStyleREL, &lv_style_plain);
skillsButtonStyleREL.body.main_color = LV_COLOR_GREEN;
skillsButtonStyleREL.body.grad_color = LV_COLOR_GREEN;
skillsButtonStyleREL.body.radius = 0;
skillsButtonStyleREL.body.border.color = LV_COLOR_BLACK;
skillsButtonStyleREL.body.border.width = 2;
skillsButtonStyleREL.body.border.opa = LV_OPA_50;
skillsButtonStyleREL.body.opa = LV_OPA_COVER;
skillsButtonStyleREL.text.color = LV_COLOR_WHITE;

//Creates Skills Button Press Style
lv_style_copy(&skillsButtonStylePR, &lv_style_plain);
skillsButtonStylePR.body.main_color = LV_COLOR_LIME;
skillsButtonStylePR.body.grad_color = LV_COLOR_LIME;
skillsButtonStylePR.body.radius = 0;
skillsButtonStylePR.body.border.color = LV_COLOR_BLACK;
skillsButtonStylePR.body.border.width = 2;
skillsButtonStylePR.body.border.opa = LV_OPA_50;
skillsButtonStylePR.body.opa = LV_OPA_COVER;
skillsButtonStylePR.text.color = LV_COLOR_WHITE;

lv_style_copy(&selectionLabelStyle, &lv_style_plain);
selectionLabelStyle.text.color = LV_COLOR_WHITE;


//Creates Red Close Side Button
redCloseButton = lv_btn_create(lv_scr_act(), NULL);
lv_obj_set_free_num(redCloseButton, 1); /*Set a unique number for the button*/
lv_btn_set_action(redCloseButton, LV_BTN_ACTION_CLICK, btn_click_action); //set function to be called when button is pressed
lv_btn_set_style(redCloseButton, LV_BTN_STYLE_REL, &redButtonStyleREL); //set the released style
lv_btn_set_style(redCloseButton, LV_BTN_STYLE_PR, &redButtonStylePR); //set the pressed style
lv_obj_set_size(redCloseButton, 200, 50); //set the size
lv_obj_align(redCloseButton, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 10); //align to top left of screen

//Creates Red Far Side Button
redFarButton = lv_btn_create(lv_scr_act(), NULL);
lv_obj_set_free_num(redFarButton, 2); /*Set a unique number for the button*/
lv_btn_set_action(redFarButton, LV_BTN_ACTION_CLICK, btn_click_action); //set function to be called when button is pressed
lv_btn_set_style(redFarButton, LV_BTN_STYLE_REL, &redButtonStyleREL); //set the released style
lv_btn_set_style(redFarButton, LV_BTN_STYLE_PR, &redButtonStylePR); //set the pressed style
lv_obj_set_size(redFarButton, 200, 50); //set the size
lv_obj_align(redFarButton, NULL, LV_ALIGN_IN_TOP_RIGHT, -10, 10); //align to top right of screen

//Creates Blue Close Side Auton Button
blueCloseButton = lv_btn_create(lv_scr_act(), NULL);
lv_obj_set_free_num(blueCloseButton, 3); /*Set a unique number for the button*/
lv_btn_set_action(blueCloseButton, LV_BTN_ACTION_CLICK, btn_click_action); //set function to be called when button is pressed
lv_btn_set_style(blueCloseButton, LV_BTN_STYLE_REL, &blueButtonStyleREL); //set the released style
lv_btn_set_style(blueCloseButton, LV_BTN_STYLE_PR, &blueButtonStylePR); //set the pressed style
lv_obj_set_size(blueCloseButton, 200, 50); //set the size
lv_obj_align(blueCloseButton, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 10, 10); //align to bottom left of screen

//Creates Blue Far Side Auton Button
blueFarButton = lv_btn_create(lv_scr_act(), NULL);
lv_obj_set_free_num(blueFarButton, 4); /*Set a unique number for the button*/
lv_btn_set_action(blueFarButton, LV_BTN_ACTION_CLICK, btn_click_action); //set function to be called when button is pressed
lv_btn_set_style(blueFarButton, LV_BTN_STYLE_REL, &blueButtonStyleREL); //set the released style
lv_btn_set_style(blueFarButton, LV_BTN_STYLE_PR, &blueButtonStylePR); //set the pressed style
lv_obj_set_size(blueFarButton, 200, 50); //set the size
lv_obj_align(blueFarButton, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -10, 10); //align to bottom right of screen

//Creates Skills Button
skillsButton = lv_btn_create(lv_scr_act(), NULL);
lv_obj_set_free_num(skillsButton, 5); /*Set a unique number for the button*/
lv_btn_set_action(skillsButton, LV_BTN_ACTION_CLICK, btn_click_action); //set function to be called when button is pressed
lv_btn_set_style(skillsButton, LV_BTN_STYLE_REL, &skillsButtonStyleREL); //set the released style
lv_btn_set_style(skillsButton, LV_BTN_STYLE_PR, &skillsButtonStylePR); //set the pressed style
lv_obj_set_size(skillsButton, 200, 50); //set the size
lv_obj_align(skillsButton, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, -10); //align to top mid of screen

//Creates Red Close Side Auton Button Label
redCloseButtonLabel = lv_label_create(redCloseButton, NULL);
lv_label_set_text(redCloseButtonLabel, "Red Close Side Auton");

//Creates Red Far Side Auton Button Label
redFarButtonLabel = lv_label_create(redFarButton, NULL);
lv_label_set_text(redFarButtonLabel, "Red Far Side Auton");

//Creates Blue Close Side Auton Button Label
blueCloseButtonLabel = lv_label_create(blueCloseButton, NULL);
lv_label_set_text(blueCloseButtonLabel, "Blue Close Side Auton");

//Creates Blue Far Side Auton Button Label
blueFarButtonLabel = lv_label_create(blueFarButton, NULL);
lv_label_set_text(blueFarButtonLabel, "Blue Far Side Auton");

//Creates Skills Button Label
skillsButtonLabel = lv_label_create(skillsButton, NULL);
lv_label_set_text(skillsButtonLabel, "Programming Skills");

//Creates Selection Label
selectionLabel = lv_label_create(lv_scr_act(), NULL);
lv_label_set_text(selectionLabel, "Select Auton");
lv_obj_align(selectionLabel, NULL, LV_ALIGN_CENTER, 0,0);

}
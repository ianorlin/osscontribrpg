#include<iostream>
/*Copyright 2014 Brendan Perrine This code is realsed on the gpl v2 
It is a simple gmae where you play as an open source contributor and try not to be crazy in which case you lose. or get to the victory level in which case you win 
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*/

#include<cstdlib>
#include<cmath>
#include<list>
#include<string>
 
using namespace std;

class Player{
public:
Player();
Player( unsigned int s_irc_level, unsigned int s_documentation_level, unsigned int s_QA_level, unsigned int s_dev_level,unsigned int s_stress_level,  unsigned int s_stress_tolerance, unsigned int s_vict_level);
//contrib choice
void contrib_irc();
void contrib_documentation();
void contrib_QA();
void contrib_dev();

//acessor functions
unsigned int get_irc_level();
unsigned int get_documentation_level();
unsigned int get_QA_level();
unsigned int get_dev_level();
unsigned int get_stress_level();
unsigned int get_vict_level();
bool is_overstressed();
bool do_i_win();
//mutators for levels
void level_up(unsigned int &  may_level_this) ;
void chance_stress();
void rest();

private:
unsigned int stress_level;
unsigned int irc_level;
unsigned int documentation_level;
unsigned int QA_level;
unsigned int dev_level;
unsigned int stress_tolerance;
unsigned int vict_level;

};

class Named_Player: public Player{
public:
Named_Player();
Named_Player( string ins_Name);
string get_name();

private:
string name;

};
void console_input_contribution(Player & conplay);
void console_input_vict_printer(Player victor);
Player custom_char_builder();
void Turn ( Player& cur_player );
bool console_choose_custom_game();
int main(){
srand(time(0));
//cout<<rand() %20<<endl;
if (console_choose_custom_game())
{
Player custom_console_player= custom_char_builder();
//check if cheating using .do_i_win() or if you are starting out crazy and print message
if (custom_console_player.do_i_win())
{
    cout<<"You have not even played yet you cheater do not try to win before playingi."<<endl;
}
else if (custom_console_player.is_overstressed()){
cout<<"You are already crazy you should care for your mental health and take care of yourself and not try to become some sort of martyr for free software and not taking care of yourself."<<endl;
}
//else use do loop to go trhough the custom game 
else {
Turn( custom_console_player);
if (custom_console_player.is_overstressed())
  { 
cout<<"Your custom character loses his/her sanity and descends into madnessi."<<endl;

  }
else { 
  console_input_vict_printer( custom_console_player);
   }
  }
}
else{

Player console_user=Player();

Turn (console_user);
//end game conidtions of win or lose. 
if (console_user.is_overstressed() )
{
cout<<"console user is over stressed and loses his or her sanity. "<<endl;
}
else {
console_input_vict_printer (console_user);
}
}
return 0;
}
/** Defualt player constructor 
Sets all levels to zero and then stress stress tolerance to 6
*/
Player::Player(){
stress_level=0;
irc_level=0;
documentation_level=0;
QA_level=0;
dev_level=0;
stress_tolerance=6;
vict_level=10;
}
/** returns irc_level */
inline unsigned int Player::get_irc_level(){
return irc_level;
}
/** returns documentation_level */
inline unsigned int Player::get_documentation_level(){
return documentation_level;
}
/** returns QA_level    */
inline unsigned int Player::get_QA_level(){
return QA_level;
}
inline unsigned int Player::get_dev_level(){
return dev_level;
}
/** meant to be called by the contrib memeber fucntions to have a common code for level up all different areas on the objects internal varibles is a member fucntion so has permssion to access 
so if you had a player named ian contibuting to QA 
ian.level_up( ian.irc_level) 
*/
void Player::level_up( unsigned int & may_level_this){

unsigned int min_to_level=14;
unsigned int dice_sides=20;
if( rand() % dice_sides >= min_to_level){
may_level_this++;
}
}
/**This function is the change that the contribution increases stress on the player call after chose an distion 
if you roll too low your stress will increase and you could lose.
*/

void Player::chance_stress(){
unsigned int stress_roll_num=3;
//less or equal to increases  than increase stress for player
unsigned int dice_sides =20;
if (rand() % dice_sides <= stress_roll_num)
{
stress_level++;
}
return;
}
void Player::contrib_irc(){
cout<<"You help some people on IRC with their minor problems."<<endl;
//chacne for level up irc level
this->level_up(irc_level);
}

void Player::contrib_documentation(){
cout<<"You contribute to documentation updating woefully out of date information on the wiki."<<endl;
this->level_up(documentation_level);
}

void Player::contrib_QA(){
cout<<"You contribute to QA and find a few minor bugs"<<endl;
this->level_up(QA_level);
}

void Player::contrib_dev(){
cout<<"You contribute to development and fix a bug and add a feature"<<endl;
this->level_up(dev_level);
}
/* Main way for now to get input from player from console can be replaced by nicer front end but not sure now 
Needs passed by refrence so players have a chance to level up
conplay is the player on the console
*/
void console_input_contribution(Player & conplay){
char how_to_help;
cout<<"Enter i to help with IRC, d to help with documentation, Q to help with QA and, D to help with development"<<endl;
cin>>how_to_help;
//stress increase in if or else if otherwise could get stressed after resting 
if(how_to_help=='i'){
conplay.contrib_irc();
conplay.chance_stress();
}
else if (how_to_help=='d'){
conplay.contrib_documentation();
conplay.chance_stress();
}
else if (how_to_help=='Q'){
conplay.contrib_QA();
conplay.chance_stress();
}
else if (how_to_help=='D'){
conplay.contrib_dev();
conplay.chance_stress();
}
else{
//no stress increase just after resting 
conplay.rest();
}


}

void Player::rest(){
unsigned int rest_min_roll=11;
unsigned int rest_num_sides=20;
cout<<"You try to rest to reduce your stress"<<endl;
if (rand()% rest_num_sides >= rest_min_roll&& this->stress_level!=0)
{
this->stress_level--;
cout<<"The relaxation was nice and reduces your stress level"<<endl;
} 

}
bool Player::is_overstressed(){

return stress_level>=stress_tolerance;
}
unsigned int Player::get_stress_level(){
return stress_level;
} 
//returns if you win true if the player wins false if does not.  

bool Player::do_i_win(){
//long if else if of all useing get 
if (this->irc_level>=this->vict_level)
{
return true;
}
else if (this->documentation_level>= this->vict_level)
{
return true;
}
else if (this->QA_level>= this->vict_level)
{
return true;
}
else if (this ->dev_level>=this->vict_level)
{
return true;
}
else {
return false;
}
}

void console_input_vict_printer(Player victorous_player
){
if (victorous_player.get_irc_level()>=victorous_player.get_vict_level())
{
cout<<"You become an irc operator and great helper making the users of $distro well supported and helped. You also prevent spammers and trolls from wrecking the expirence for everyone."<<endl;
}
else if (victorous_player.get_documentation_level()>=victorous_player.get_vict_level()){
cout<<"You become a great contributor to documentation helping people online understand even through many thankless hours and espicailly helful to other trying to help on irc from links to your work."<<endl;
}
else if (victorous_player.get_QA_level()>=victorous_player.get_vict_level()){
cout<<"You become a great QA engineer finding bugs and even fixing them in development relase and making users lives much better. You even prevent a bug that would be a major issue like many people being unable to connect to wifi."<<endl;
}
else {
cout<<"You become a great dev helping write the open source software that so many depend on"<<endl;
}
}
unsigned int Player::get_vict_level(){
return vict_level;
}
/**
constructor with paramaters for player 
s_*_level is the starting level for each part of a player object.
Copy things starting with s into the value for Player class without starting with s
s is short for start 
*/
Player::Player( unsigned int s_irc_level, unsigned int s_documentation_level, unsigned int s_QA_level, unsigned int s_dev_level, unsigned int s_stress_level, unsigned int s_stress_tolerance,  unsigned int s_vict_level){
irc_level=s_irc_level;
documentation_level=s_documentation_level;
QA_level=s_QA_level;
dev_level=s_dev_level;
stress_level=s_stress_level;
stress_tolerance=s_stress_tolerance;
vict_level=s_vict_level;

}

/** This function gets input from player asking if they want a custom game
It returns true if the player enters y for a custom game and false if any other input.
*/
bool console_choose_custom_game(){
char cust_accept='y';
cout<<"Enter "<<cust_accept<<" if you want to play a custom game"<<endl;
char cust_input;
cin>>cust_input;
if (cust_input==cust_accept){
return true;
}
else{
return false;
}
}
Player custom_char_builder(){ 
//get contrib levels
cout<<"Insert your irc level"<<endl;
unsigned int cust_irc_level;
cin>>cust_irc_level;
cout<<"Insert your Documentation elvel"<<endl;
unsigned int cust_documentation_level;
cin>>cust_documentation_level;
unsigned int cust_QA_level;
cout<<"Insert your QA level"<<endl;
cin>>cust_QA_level;
unsigned int cust_dev_level;
cout<<"Insert your dev level"<<endl;
cin>>cust_dev_level;
//stress
cout<<"enter your current stress level"<<endl;
unsigned int cust_stress_level;
cin>>cust_stress_level;
cout<<"enter your stress tolerance"<<endl;
unsigned int cust_stress_tolerance;
cin>> cust_stress_tolerance;

//victory 
cout<<"Enter the level of one contribution needed to attain victory"<<endl;
unsigned int cust_vict_level;
cin>>cust_vict_level;

Player cust_char= Player(cust_irc_level, cust_documentation_level, cust_QA_level, cust_dev_level,cust_stress_level, cust_stress_tolerance,cust_vict_level); 

return cust_char;
} 
/**
Iterate a turn on the console passes cur_player by reference and gets input and shows the status of player. 
modified from loop in main to allow not duplicated code for custom game or defualt game if not playing a custom one. 
Does not work for multiplayer as is needed to take turns for each player in sequentially.  
*/
void Turn ( Player & cur_player){
do{
console_input_contribution(cur_player);
//console_user.chance_stress();
cout<<"irc_level "<<cur_player.get_irc_level()<<"documentation_level "<<cur_player.get_QA_level()<<"QA level "<< cur_player.get_dev_level()<<"dev level"<<cur_player.get_dev_level()<<"Stress level "<<cur_player.get_stress_level()<<endl;
}while (!cur_player.is_overstressed()&&!cur_player.do_i_win());

}

/**This function asks whether or not you want to make a multiplayer console game. 
Returns true if multiplayer game and false otherwise. 

*/
bool console_multiplayer_game(){
char multiplayer_accept='y';
char multiplayer_input;
cin>>multiplayer_input;
if (multiplayer_input=='y')
{
return true;
}
else 
{
return false;
}
}

/**Default constructor for named player
sets default name to Player
*/
Named_Player::Named_Player() :Player() 
{
name="Player";
}

Named_Player::Named_Player(string ins_name) :Player(){
name=ins_name;
}

#include<iostream>
/*Copyright 2014 Brendan Perrine This code is realsed on the gpl v2 

*/

#include<cstdlib>
#include<cmath>
 
using namespace std;

class Player{
public:
Player();
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
void console_input_contribution(Player & conplay);
void console_input_vict_printer(Player victor);

int main(){
srand(time(0));
//cout<<rand() %20<<endl;
Player console_user=Player();
do{
console_input_contribution(console_user);
//console_user.chance_stress();
cout<<"irc_level "<<console_user.get_irc_level()<<"documentation_level "<<console_user.get_QA_level()<<"QA level "<< console_user.get_dev_level()<<"dev level"<<console_user.get_dev_level()<<"Stress level "<<console_user.get_stress_level()<<endl;
}while (!console_user.is_overstressed()&&!console_user.do_i_win());
//need to add victory conditions 
//call contrib in area 
//check if game is over
//repeat
//loss message 

if (console_user.is_overstressed() )
{
cout<<"console user is over stressed and loses his or her sanity. "<<endl;
}
else {
console_input_vict_printer (console_user);
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
cout<<"You become an irc operating and great helper making the users of $distro well supported and helped."<<endl;
}
else if (victorous_player.get_documentation_level()>=victorous_player.get_vict_level()){
cout<<"You become a great contributor to documentation helping people online understand even through many thankless hours and espicailly helful to other trying to help on irc."<<endl;
}
else if (victorous_player.get_QA_level()>=victorous_player.get_vict_level()){
cout<<"You become a great QA engineer finding bugs and even fixing them in development relase and making users lives much better."<<endl;
}
else {
cout<<"You become a great dev helping write the open source software that so many depend on"<<endl;
}
}
unsigned int Player::get_vict_level(){
return vict_level;
}

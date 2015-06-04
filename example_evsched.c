#define interval 100
int counter1 = 0;
char running1 = 0;

void setup(){
long pmillis = millis();
}

void loop(){
ev_sched()
}


void ev_sched{
    if( (millis()-pmillis) >= interval){
    //this runs periodically
    if(running1){
        switch(counter1){

        case 1:
           //first step in animation
           break;
        case 2:
            //2nd step and so forth
            //.....
            break;
        case 100:
            running1=0;
            counter1=0;
       }

    }   
}

 
inherit ROOM; 
void create() 
{ 
        set("short", "棋牌室"); 
        set("long", @LONG 
这是为无聊人士开放的麻将棋牌室,是大家放松精神的好地方。
友情提示:赌博有碍身体健康。
LONG 
           ); 
        set("exits", ([ 
                 
                  "down" : "/d/city/chmiao"
           ]));

        set("objects",  ([  
                
//                 "/u/spiderii/mj" : 1,
            ])); 

        set("no_death", 1);
        set("no_fight", 1);
        setup();
}


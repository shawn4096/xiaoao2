// Room: /d/city/dangpu.c
// Update by lsxk@hsbbs 2007/7/19

#include <ansi.h>;

inherit ROOM;

mapping *special=({
([]),
([]),
([]),
([]),
([]),
([]),
([]),
([]),
([]),
([]),
([]),
([]),
([]),
([]),
([]),
([]),
([]),
([]),
([]),
([]),
([]),
([]),
([]),
([]),
([]),
([]),
([]),
([]),
([]),
([]),
([]),
([]),
([]),
([]),
([]),
([]),
([]),
([]),
([]),
([]),
([]),
([]),
([]),
([]),
});


void getspec();

void create()
{
	set("short", "当铺");
	set("long", 
"这是一家素以买卖公平著称的老字号当铺，一个四尺高的柜台摆在你的面\n"+
"前，柜台上摆着一个牌子(paizi)， 柜台后坐着当铺的老板，一双鬼溜溜的眼\n"+
"睛上上下下打量着你，听说这里正在大量收讫『"+HBGRN+HIG+"书剑通宝"+NOR+"』。\n"
);
	set("no_fight",1);
	set("no_sleep_room",1);
	set("objects", ([
           __DIR__"npc/huang" : 1,
           __DIR__"npc/mm2" : 1,
	]));
	set("exits", ([
         "north" : __DIR__"guangchangnan",
	]));

	set("coor/x",110);
  	set("coor/y",-30);
   	set("coor/z",0);
	getspec();
	setup();
}

void init()
{
    object me = this_player();
    object obj;

    if(!objectp(me)) return;
/*
    if(!present("tongbao xiang", me) && (!random(100)||me->query("id")=="zmud")){
        message_vision(HIC"突然，$N发现从当铺柜台上掉下来一样东西，但是忙碌的老板和伙计们都没发现。\n$N连忙将东西藏在了自己身上。\n"NOR,me);
        if(!wizardp(me))
        me->add_busy(3+random(3));
        if(!present("tongbao xiang",environment(me)) ){
            obj = new("/clone/gift/credit_box");
            obj->move(me);
        }
    }
*/
	add_action( "do_exchange", "duihuan" );
	add_action( "do_look", "look" );
	/*if (me->query("SJ_Credit",1)>60000)
	{
		me->set("SJ_Credit",25001);
		return;
	}*/
}

void getspec()
{
	mixed *file;
	int i;
	object ob;
	string tpw;
	
	file = get_dir("/clone/spec/");

	if( !sizeof(file) ) return notify_fail("找不到任何物品 \n");
	for( i = 0; i < sizeof(file); i++ )
	{	tpw = "";
                file[i] = "/clone/spec/" + file[i];
                if( file_size(file[i]) < 0 ) continue;
		ob = new(file[i]);
		
		if(!objectp(ob)) continue;		
		if(!ob->query("credit")) continue;		
		
		if (!ob->query("rest"))
			tpw = "无";		
		else
			tpw = "每周"+chinese_number(ob->query("rest"))+"次";	
		special[i]=([
			"value"		:	ob->query("credit"),
			"name"		:	ob->query("name"),
			"id"		:	ob->query("id"),	
			"desc"		:	ob->query("desc"),	
			"degree"	:	ob->query("degree"),
			"tpw"		:	tpw, 
			"file"		:	file[i]
			 ]);
		destruct(ob);	
	}
}


int do_look(string arg) 
{       
	object me = this_player();
	int i;
        
	if(me->is_busy()) 
		return notify_fail("你正忙着呢。\n");
        	
 
        if (arg == "paizi" ){   
	        write(query("special"));
	        write("公平交易，老少无欺。\n");
	        write("本店现在收纳“书剑通宝”，可用书剑通宝兑换的限制级宝物如下：\n");
                write("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
                write(sprintf("┃ %-25s  %-45s  %-10s %-12s %-7s┃\n", "宝物名称","宝物作用","可用次数","使用限制","通宝" ));
                write("┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
	        for (i=0;i<sizeof(special);i++) {
	        	 if (!special[i]["value"]) continue;
          write(sprintf("┃ %-25s  %-46s %-10s %-12s "+HIY+"%-7d"+NOR+"┃\n", special[i]["name"]+"("+special[i]["id"]+")",special[i]["desc"],chinese_number(special[i]["degree"])+"次",special[i]["tpw"],special[i]["value"] ));
	        }
                write("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
	        write("请使用（duihuan xxxx）指令来兑换获得。\n");
		return 1;
	}     
	return 0;
}

int do_exchange(string arg) 
{
   int i,j,k;
   object card,ob,me = this_player();
	
	if(me->is_busy()) 
		return notify_fail("你正忙着呢。\n");
  		
	if(!arg)
		return notify_fail("你想兑换什么。\n"); 
  		
	for (i=0;i<sizeof(special);i++)
	if (arg == special[i]["id"])  
		j=i+1;	
	if(!j)
		return notify_fail("这里没有你想兑换东西。\n");
        
        if (me->query("quest/bwdh/card_winner") && present("vip card", me)
          &&special[j-1]["value"]*(int)me->query("quest/bwdh/card_winner")>me->query("SJ_Credit")*100)
           return notify_fail("对不起你现有的通宝不够兑换"+special[j-1]["name"]+"。\n");
        else if (special[j-1]["value"]>me->query("SJ_Credit"))
		return notify_fail("对不起你现有的通宝不够兑换"+special[j-1]["name"]+"。\n");
        
	ob = new(special[j-1]["file"]);
	if(!objectp(ob))
		{return notify_fail("系统错误请联系WIZ。\n");}
		
   if(me->query("quest/bwdh/card_winner") && present("vip card",me)){
    card = present("vip card",me);
   me->add("SJ_Credit",-(special[j-1]["value"]*(int)me->query("quest/bwdh/card_winner")/100));
   me->add("SJ_Credit_Used",(special[j-1]["value"]*(int)me->query("quest/bwdh/card_winner")/100));
   k = special[j-1]["value"]*(int)me->query("quest/bwdh/card_winner")/100;
   message_vision(sprintf(HIC"%s一把掏出怀里的%s"HIC"对这当铺老板指了指%s"HIC"道：“就它了，给俺换！”\n"NOR,me->query("name"),card->query("name"),special[j-1]["name"]),me);
   message_vision(sprintf(HIG"当铺老板接过%s"HIG"一看，诧异的看着%s,连忙道：“原来是本店贵宾！请稍坐片刻，立即给您办妥！\n"NOR,card->query("name"),me->query("name")),me);
   }
   else{
	me->add("SJ_Credit",-special[j-1]["value"]);
	me->add("SJ_Credit_Used",special[j-1]["value"]);
   }
   ob->move(me);
   if(me->query("quest/bwdh/card_winner") && present("vip card",me)){
   message_vision(sprintf("当铺老板吆喝一声：“VIP客户:%s兑换限制级宝物%s，"+me->query("quest/bwdh/card_winner")/10+"折优惠，收讫%s个书剑通宝。”\n",me->query("name"),special[j-1]["name"],chinese_number(k)),me);
    }
   else
	message_vision(sprintf("当铺老板吆喝一声：“%s兑换限制级宝物%s，收讫%s个书剑通宝。”\n",me->query("name"),special[j-1]["name"],chinese_number(special[j-1]["value"])),me);
	tell_object(me,"您目前还剩"
		+ chinese_number(me->query("SJ_Credit"))+"个书剑通宝，您已经累计消费了" 
		+ chinese_number(me->query("SJ_Credit_Used")) +"个书剑通宝。\n");
	log_file( "static/CREDIT",sprintf("%s(%s) | 购买%s | 剩:%s | 用:%s | 累计:%s.\n", me->name(), me->query("id"), special[j-1]["name"],chinese_number(me->query("SJ_Credit")),chinese_number(special[j-1]["value"]),chinese_number(me->query("SJ_Credit_Used"))));
        me->start_busy(1);
		
	return 1; 
}

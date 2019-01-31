// mr up_misc_skills.c
// be jpei 2010

#include <ansi.h>
#include <room.h>
inherit ROOM;
void create()
{
	set("short",HIW"娘缳玉洞-杂项部"NOR);
	set ("long",@long
这是曼佗罗山庄存放武功秘籍的地方，一排排书架上整齐的摆放着各种书
籍，似乎都与如何研修更高深的杂项武学有关。
long);
	set("exits",([
		"out" : __DIR__"huandong",
	]));


	set("no_fight", 1);
	setup();
}

void init()
 {
         add_action("do_canwu", "canwu"); 
         add_action("do_canwu", "yandu");
 }

/*

int do_canwu(string arg)
 {
     object me = this_player();

     if(arg != "misc" )
           return notify_fail("这里只能参悟杂学(misc)部分!\n");

     if (me->is_busy() || me->is_fighting()|| me->query_temp("con_gift") )
                  return notify_fail("你正忙着呢。\n");

if (me->query_temp("canwu_now") )
       return notify_fail("你正忙着呢。\n");

if (me->query("relife/gifts/now") )
       return notify_fail("你还是先把自己的天赋分配完毕以后再来吧。\n");
        
        if (query_temp("canwu") )
        return notify_fail("有人正在参悟呢，你等一会把。\n");


     if( me->query("combat_exp",1)<25000000)
                 return notify_fail("你胡乱的翻了翻书架上的藏书，发现里面的内容高深莫测，无法理解，不由得摇了摇头。\n");
       
     
       message_vision( HIW"$N仔细的翻看着书架上的藏书，对里面瀚如烟海的杂学内容很感兴趣。\n"NOR,me);
        message_vision( HIW"$N一头扎进书堆里.不停的翻看着。。 \n"NOR, me);
       me->start_busy(100);               
       me->set_temp("canwu_now",1); 
       set_temp("canwu",1);            
     call_out("thinking",5, me );
         return 1;

 }


int thinking(object me)
{
  int i,j,p,exp;
  p = me->query("str",1)+ me->query("dex",1)+ me->query("con",1)+ me->query("int",1);
 if(!me) return 0;
	
 if(me->query_temp("con_gift")<(3+random(3)))
       {  me->add_temp("con_gift",1);
          if(random(2)) tell_object(me,HIG"\n你仔细的研读着书里面的内容，只觉得耳目一新...\n"NOR);
                   else tell_object(me,HIY"\n你研读着书里千奇百怪的杂学内容，心里有所领悟...\n"NOR);  

	  tell_room(environment(me),HIC""+me->query("name")+"眉头紧皱，似乎在思索着什么...\n"NOR, ({}));

	  remove_call_out("thinking");
	  call_out("thinking",3+random(3), me);

	}

 else { 
         me->delete_temp("con_gift");
         me->start_busy(1);     
  message_vision(HIC"\n$N「哈哈哈」大笑几声，说道：“原来如此，原来如此。”\n"NOR,me); 
  tell_object(me,HIR"\n你通过本次研读，对闯荡江湖的见识更加深了一步！\n"NOR);
  tell_object(me,HIR"\n想起了自己以前走过的不少弯路，不禁大感后悔！你决定背叛师门，重入江湖！\n"NOR);
  tell_object(me,HIW"你获得了一次重新拜师的机会！\n"NOR);
  tell_object(me,HIR"\n你的天赋属性被重置了！你可以立即重新分配自己的天赋属性\n"NOR); 
  tell_object(me,HIR"\n你重新审视起自己年轻时代笑傲江湖的梦想！\n"NOR);    
  tell_object(me,HIW"你进入了快速成长的黄金时代！\n"NOR);    

        me->set("str",10);
        me->set("dex",10);
        me->set("con",10);
        me->set("int",10);
        //me->delete("gf_gives");

		me->delete("class");
		me->set("relife/gifts/total", p-40 );
        me->set("relife/gifts/now",   p-40 );
        me->delete("relife/gifts/used");
        
        
        
        
        
        
        
               exp = 5000000;
       if(me->query("registered") == 3) exp=4500000;
       if(me->query("y-card-vip"))         exp=4250000;
       if(me->query("buyvip") )             exp=4000000; 
       me->add("combat_exp",-exp);
        me->delete("family",1);                  
        me->add_condition("db_exp",6666);
        me->set("age",18);
        me->set("shen",1);
        me->set("title",HIC"武林神话"NOR);
       i = me->query("relife/gifts/now",1); 
       j = me->query("relife/gifts/total",1);
   
    tell_object(me,HBBLU"\n你本次参悟共耗费了" + HIW + chinese_number( exp ) + HIR + "实战经验，你现在总共有" + HIW + chinese_number( i ) + HIR + "的额外的天赋！\n"NOR);
    tell_object(me,HBRED"\n请立即使用(addgift)进行分配！\n"NOR);

      log_file("canwu/getmisc", sprintf("%s(%s) 耗费500万经验，重置天赋点数为%d，当前经验：%d。\n", 
       me->name(1),
       me->query("id"),
       me->query("relife/gifts/total",1),
       me->query("combat_exp")) );
  me->delete_temp("canwu_now");   
 delete_temp("canwu");   
   }

}

*/
// houyuan.c 后山小院
// By Spiderii@ty 加入yttlg quest
#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
	set("short", "后山小院");
	set("long", @LONG
这是后山的一座小院，布置简简单单，除了一床、一桌、一椅、一蒲团，
再也没有别的什物。比较引人注目的是墙上挂着一把剑。这里就是武当开山祖
师张三丰的练功所在。
LONG
	);

	set("exits", ([
                "north" : __DIR__"yuanmen",
	]));

	set("cant_hubiao", 1);

	set("objects", ([
                CLASS_D("wudang")+"/zhang" : 1 
        ]));

        create_door("north", "竹门", "south", DOOR_CLOSED);
        setup();
}
void init()
{
  object me=this_player();
  
  if (me->query_temp("quest/yttlg/story1"))
  {
     tell_object(me,HIW"你奔到张三丰面前一跪，泣不成声，叫道：“师父，师……父………三……三哥受人暗算……\n"NOR); 
     tell_object(me,HIW"张三丰见爱徒伤成这般模样，胸中大震，当下不暇询问。奔进内堂取出一瓶“白虎夺命丹”。\n"NOR);       
     tell_object(me,HIW"丹瓶口本用白蜡封住，这时也不及除蜡开瓶，左手两指一捏，瓷瓶碎裂，取出三粒白色丹药。\n"NOR); 
     tell_object(me,HIW"但俞岱岩知觉已失，哪里还会吞咽？。\n"NOR);       
     tell_object(me,HIW"张三丰双手食指和拇指虚拿，成“鹤嘴劲”势，以食指指尖点在俞岱岩耳尖上三分处的“龙跃窍”\n"NOR); 
     tell_object(me,HIW"以他此时功力，这“鹤嘴劲点龙跃窍”使将出来，便是新断气之人也能还魂片刻，但他手指直摆到二十下，俞岱岩仍是动也不动。\n"NOR);       
     remove_call_out("liaoshang");
     call_out("liaoshang", 10, me);         
  }
     add_action("do_linmo", "linmo");    

}
void liaoshang(object me)
{
  if(!me) return;

   tell_object(me,HIW"\n张三丰轻轻叹了口气，双手捏成剑诀，掌心向下，两手双取俞岱岩“颊车穴”。\n"NOR); 
   tell_object(me,HIW"\n那“颊车穴”就在腮上牙关紧闭的结合之处，张三丰阴手点过，立即掌心向上。\n"NOR);
   tell_object(me,HIW"\n翻成阳手，一阴一阳，交互变换，翻到第十二次时，俞岱岩终于张开了口,缓缓将丹药吞入喉中。\n"NOR); 
   tell_object(me,HIW"\n你一直提心吊胆，这时“啊”的一声，才叫了出来。\n"NOR);
   tell_object(me,HIW"\n但俞岱岩喉头肌肉僵硬，丹药虽入咽喉，却不至腹。你不由得伸手按摩他喉头肌肉。\n"NOR); 
   tell_object(me,HIW"\n张三丰随即伸指闭了俞岱岩肩头“缺盆”、“俞府”诸穴，尾脊的“阳关”、“命门”诸穴，让他醒转之后，不致因四肢剧痛而重又昏迷。\n"NOR);
   remove_call_out("liaoshang1");
   call_out("liaoshang1", 10, me);      


}
void liaoshang1(object me)
{
  if(!me) return;
   tell_object(me,HIW"\n这时外面传来都大锦请求拜见的声音,你不禁怒上心头,说道:就是这斯,害我三师哥。\n"NOR); 
   tell_object(me,HIW"\n张三丰摆摆手道:莫急,事情终究要问个水落石出的。你且叫他进来。\n"NOR); 
   tell_object(me,HIW"\n你强压住怒火,将都大锦叫了进来,张三丰趁机仔细询问了事情的整个经过。\n"NOR);  
   tell_object(me,HIW"\n都大锦说完后,张三丰不由的长叹一声:屠龙宝刀再见江湖,从此又是多事之秋了。\n"NOR);
   tell_object(me,HIW"\n张三丰道：今晚这杯寿酒也不用再喝了。一个月之后，叫你诸位师兄弟来此相聚\n"NOR); 
   tell_object(me,HIW"\n张三丰说道:岱岩倘若不治，师兄弟也可和他再见上一面。”说到这里，不禁凄然。\n"NOR);
   tell_object(me,HIW"\n张三丰大袖一挥,说道:你且退下吧。\n"NOR); 
   me->delete_temp("quest/yttlg/story1");
   me->set_temp("quest/yttlg/story2",1);
}
int do_linmo(string arg)
{
        int improve, cost, lv;
        object me = this_player();
        
        improve = me->query_int() / 10 + random(me->query_int() * 5 / 6);
        improve /= 2;
        if( !arg || arg=="" ) return 0;
        
        if( (int)me->is_busy() || me->is_fighting()) 
        	return notify_fail("你正忙着呢。\n");
         	
        if (arg == "手势" ){             
            	if(!me->query("quest/yttlg/pass") || !me->query_skill("yitian-tulong", 1))  
               		return notify_fail("你想临摹什么?\n");
      if( me->query_skill("yitian-tulong", 1) == 100 )
                            return notify_fail("你已经将倚天屠龙功融会贯通了!\n");
        	cost = 600 / (int)me->query("int");
        	cost = 600 / (int)me->query("int");

    	if ((int)me->query("jingli") < cost || (int)me->query("jing") < cost){
                	message_vision("$N耗费精神过度，一下晕了过去。\n",me);
                	me->unconcious();
                	return 1;
                } 
	if ( me->query_skill("yitian-tulong", 1) > 99 ){
        //天赋“领悟大师”影响效果：  by spiderii@ty ..lsxk想法太过变态了
        lv = me->query("max_pot")-100;
        if(me->query("relife/quest/lwds")){
         if(random(100) > me->query("relife/quest/lwds")*10)
            write(HIC"你经过转世重修后，领悟到了武技万变不离其宗的道理，瞬间领悟到了倚天屠龙功的精华所在。\n"NOR);
            me->set_skill("yitian-tulong",lv);
            }

      }
              message_vision("$N手指在空中不停的比画,一招一式,力求尽记于心。\n"NOR, me);  
           	me->improve_skill("yitian-tulong", improve);            
           	me->receive_damage("jing", cost, "消耗过度");
           	me->receive_damage("neili", cost/2, "消耗过度");
           	me->receive_damage("jingli", cost, "消耗过度");                        
           	return 1;
        }     
        return 0;
}


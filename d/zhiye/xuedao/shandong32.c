// nroad6.c
// Modified by Java Apr.27 1998
#include <ansi.h>
inherit ROOM;
void create()
{
        set("short","练功室");
        set("long",@LONG
这是一间血刀门练功室，极为隐秘。光线极为充足，墙角堆放了
不少机关人，有些坏掉的机关人放在墙角，墙上描绘了不少彩绘，其
中大多数描绘密宗欢喜禅的图形。东边靠墙的架子上摆放了一堆堆的
纸张( paper)，地上散落几张碎纸，显然是有人在此修炼某种功夫所
致。
LONG );
        set("exits",([
                "east"   : __DIR__"shandong3",
                //"southup" : __DIR__"nroad5",
        ]));
        set("objects",([
             /*  "/clone/weapon/miandao" : 1,
				
				"/clone/weapon/xinyuedao" : 1,*/
				"/clone/weapon/blade" : 1,

        ]));
		set("item_desc", ([
			"paper" : CYN"案子上摆放着一堆堆的纸张,供血刀门弟子以刀劈（pi）纸张所用。\n"NOR,
			//"shujia" : CYN"书架上放着一堆堆的修炼秘籍，大部分为各门派的刀谱和怪异武功，\n"NOR,
		]));

        //	set("no_clean_up", 0);
       // set("outdoors", "xuedao");
        setup();
       //        replace_program(ROOM);
}
void init()
{
	object me=this_player();
	if (me->query("quest/xd/xddf/pizhi/asklaozu"))	add_action("do_pi","pi");
}

int do_pi(string arg)
{
	object me,weapon;
	me=this_player();	
	weapon=me->query_temp("weapon");	
	if (!arg||arg!="纸张")
	{
		message_vision(HIW"$N拿刀对空气劈砍了起来!\n"NOR,me);
		return 1;
	}
	
	if (weapon&&weapon->query("skill_type")!="blade")
	{
		message_vision(HIW"$N练习血刀绝技你总得找刀来装备吧！\n"NOR,me);
		return 1;
	}
	if (!me->query("quest/xd/xddf/pizhi/asklaozu"))
	{
		message_vision(HIW"$N没有得到老祖的指点，劈砍了半天不得要领！\n"NOR,me);
		return 1;
	}
	
	if (me->query_skill("xuedao-daofa",1)<500)
	{
		message_vision(HIW"$N对那一堆纸张一刀劈了下去，一下子把整个纸堆披散在地！\n"NOR,me);
		return 1;
	}
	
	if (me->query("family/family_name")!="血刀门")
	{
		message_vision(HIW"$N不是血刀门弟子，来此消遣么？\n"NOR,me);
		return 1;
	}
	
	if (QUEST_D->queryquest(me,"xd/xddf/pizhi"))	
	{
		me->set("title",HBRED"血刀刀法传人"NOR);
		me->set("mytitle/quest/xddftitle",HBRED"血刀刀法传人"NOR);
		message_vision(HIW"$N已经解开了这个谜题！\n"NOR,me);
		return 1;
	}
    
	if (QUEST_D->queryquesttime(me,"xd/xddf/pizhi"))	
	{		
		message_vision(HIW"$N来的太频繁了，武功最忌讳心气浮躁！\n"NOR,me);
		return 1;
	}
	if (!me->query("quest/xd/dichuan"))
	{
		//command("say 你");
		message_vision(HIW"$N非嫡传，血刀需要的是始终如一的忠诚弟子。\n"NOR,me);
		return 1;
	}
	if (me->query("int")<45)
	{
		//command("say 你");
		message_vision(HIW"练习血刀刀法需要的是高悟性，$N还是好好修炼去吧！\n"NOR,me);
		return 1;
	}
	if (me->query_temp("quest/xd/xddf/liandao"))
	{
		message_vision(HIW"$N正在练习批纸削腐！\n"NOR,me);
		return 1;

	}
	
	message_vision(HIW"$N运使老祖传授的运气法门，举刀劈向那堆纸张！\n"NOR,me);
	me->set_temp("quest/xd/xddf/liandao",1);
	me->start_busy(2);
	remove_call_out("liandao");
	call_out("liandao",1,me);
	return 1;
	
}

int liandao(object me)
{
  int i,j; 
  if(!me) return 0;	
  
  if(me->query_temp("canwu_liandao")<(10+random(10)))
   {  
	  me->add_temp("canwu_liandao",1);
	  switch (random(9))
	  {
		case 0:
			tell_object(me,HIG"\n你一刀劈出，一不小心把一堆纸披散在地.\n"NOR);
			break;
		case 1:
			tell_object(me,HIY"\n你仔细琢磨用刀的技巧，一刀劈出，带出十来张纸。\n"NOR);
			break;
		case 2:
			 tell_object(me,HIR"\n你连续劈出几刀，每一刀都没控制好，心中不由大急！..\n"NOR);
			 me->add_temp("canwu_liandao",-1);
			break;
		case 3:
			tell_object(me,HIW"\n你枯坐哪儿，想了想，然后又一刀劈出，把握刀的用力技巧，似乎有所心得.\n"NOR);
			break;
		case 4:
			tell_object(me,CYN"\n你自言自语，神情疲倦之际，似乎即将崩溃.\n"NOR);
			me->add_temp("canwu_liandao",-1);

			break;
		case 5:
			tell_object(me,MAG"\n你心中烦躁不堪，一刀刀劈出去，甚是恼怒.\n"NOR);
			me->add_temp("canwu_liandao",-1);

			break;
		default:tell_object(me,YEL"\n你忽然似乎有所得，一刀劈出，竟然带出来少许纸张.\n"NOR);
			break;

	  }      

	  tell_room(environment(me),HIC""+me->query("name")+"手拿长刀，一刀一刀劈向那堆纸堆，神情极为专注...\n"NOR, ({}));

	  //remove_call_out("liandao");
	  call_out("liandao",3+random(3), me);

   } 
  else	
 	{ 
          if (QUEST_D->questing(me,2,150,0,"xd/xddf/pizhi"))
		  {        
         me->start_busy(3);
		 message_vision(HIY"\n$N一刀削出，在厚厚的纸堆中只劈出一张纸，那张纸在刀气带动下，轻飘飘的落地。”\n"NOR,me); 
         message_vision(HIY"\n$N「哈哈哈」仰天大笑几声，说道：“原来如此，原来如此。”\n"NOR,me); 
         message_vision(HBYEL+HIW"\n$N经过不断刀法练习领悟，终于领悟了血刀老祖所传授的批纸削腐诀的奥秘！”\n"NOR,me); 
        
		 me->delete_temp("canwu_liandao");
		 me->delete_temp("quest/xd/xddf/liandao");
		 QUEST_D->setmytitle(me,"cxztitle",HBRED"血刀刀法真传"NOR);		 
		 return 1;
        }
	 else {
	     message_vision(HIG"\n$N长叹一生，自言自语地说道：“看来这批纸削腐诀真是不好解啊，继续努力吧。”\n"NOR,me); 
		 message_vision(HIY"\n参悟批纸削腐诀绝技解密失败！\n"NOR,me);          
		 me->start_busy(2);
		 me->delete_temp("canwu_liandao");
		 me->delete_temp("quest/xd/xddf/liandao");
		 me->delete_temp("quest/xd/xddf");
		 return 1;
       }
	}	
}
// aqing.c 越女阿青

#include <ansi.h>
inherit NPC;
inherit F_MASTER;

int ask_ynj();
//int thinking();
void create()
{

        set_name("阿青", ({ "a qing", "aqing", "qing" }) );
	    set("gender", "女性" );
        set("age", 14);
		set("per", 40);
        set("long", "一个十三四岁的小姑娘，皮肤白晰，容貌甚是秀丽，身材苗条，弱质纤纤。\n");
        set("attitude", "peaceful");
        set("beauty", "30");
        set("title", "少女");
        set("attitude", "friendly");
        set("combat_exp", 18000000);
        set("str", 30);
        set("dex", 30);
        set("int", 30);
        set("con", 30);
        set("max_neili", 25000);
        set("neili", 25000);
        set("eff_jingli", 8000);
        set("jingli", 8000);
        set("max_jing", 6000);
        set("jing", 6000);
        set("jiali", 200);
        set("max_qi", 30000);
        set("qi", 30000);
        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "sword.liujian" :)
        }));

        set_skill("sword", 600);
        set_skill("dodge",400);
        set_skill("force",  400);
        set_skill("parry",  400);
        set_skill("literate",200);
        set_skill("yunu-xinjing", 400);
        set_skill("yuenu-jian", 600);
        set_skill("yunu-shenfa",500);

        map_skill("force", "yunu-xinjing");
        map_skill("dodge", "yunu-shenfa");
        map_skill("sword","yuenu-jian");
        map_skill("parry","yuenu-jian");
        set_temp("apply/attack", 150); 
        set_temp("apply/defense", 150); 
        set_temp("apply/armor", 150); 
        set_temp("apply/damage", 150); 
        set("inquiry", ([
		   "越女剑" : (: ask_ynj :),
		   	//"绝技" : (: ask_jueji :),
		  //  "越女剑" : random(2)?"你问这个干嘛。是一位老猿曾经教我的一套剑法的秘经。":"如果你留心，当年在武馆之内就刻有神照经内功心法。嘿嘿。",
		   "范蠡" : "他是我的大哥，你问这个干什么？",
		   //"绝世武技" : "你问这个干什么？哼..有待开发，等着吧你....",
		
	])); 
        setup();

        carry_object("/d/suzhou/npc/obj/shoe")->wear();
        carry_object("/d/suzhou/npc/obj/skirt")->wear();
        carry_object("/d/suzhou/npc/obj/greensilk")->wear();
        carry_object("/d/suzhou/npc/obj/zhujian")->wield();
}
int ask_ynj()
{
    int total,i,j,t,s;
	object me = this_player();
	
	total=me->query("str")+me->query("con")+me->query("dex")+me->query("int")+me->query("per")+me->query("pur");
	i=random(me->query("kar"));
	j=random(me->query("int"));
	t=random(total);
	//随机数
	
	 s = 20;
      if(me->query("m-card-vip")) s =  18;
      if(me->query("y-card-vip")) s =  15;
      if(me->query("buyvip"))     s =  10;
      s=random(s);
	if (me->query("gender")!="女性" )
	{
     command("say 本姑娘看起来是随便教人的主么？");
	 return 1;
	}
	if (me->query("per") < 29)
	{
     command("say 你先天容貌太难看，怎么可能习得越女剑？");
	 return 1;
	}
	if (me->query("quest/ynj/pass") == "ok")
     {
     	 if(me->query("potential")<= 5){
	       command("kick "+me->query("id"));	     
	       command("say 潜能不够学什么剑法！");
           return 1;
          }
		 else{
			 message_vision("$N向$n请教有关越女剑法的奥妙。\n", me, this_object());
             me->receive_damage("jing", random(30));
             tell_object(me,"你听了阿青的指点，对越女剑的奥妙似乎有些心得。\n");
             me->add("potential",-(random(3)+2));
             if( me->query("potential")<0)
                me->set("potential",0);
             me->improve_skill("yuenu-jian", 150+random(me->query_int()*2));
             me->improve_skill("sword", random(me->query_int())/2);
			 return 1; 
			 }        
	  }
    //else{
   	  //command("say 不要调戏本姑娘，烦着呢，你再开玩笑小心我杀了你！\n");
	  //return 1;
      //}
    if( me->query("combat_exp")<10000000)
	 {
	  command("say 少于10m跟我学越女剑，你功力太浅了，先练功去吧。");
	  return 1;
	 }

    if( (time()-me->query("quest/ynj/time"))<86400)		
   	{
	  command("say 你还是去休息一下吧，没事别来烦我！");
	  return 1;
	}
	//me->start_busy(10);
      command("sigh");
	  command("say 越女剑法本不是刻意叫做越女剑法，而是当初我隐居于山林时偶尔见一位老白猿戏耍，不经意间学到的。");
      command("say 后来我认识了一个叫做范蠡的先生，受他邀请方将此剑术交给当时吴国军士。");
      command("say 这本不属于人间的剑法，没想到竟然还有人记得我这山野女子。");
	  command("say 你若真的想学就看你的机缘了！");
	  command("say 看仔细了。。。。。。。！");
	  message_vision(HIG"阿青将越女剑的招式施展出来，顿时剑光霍霍，随着阿青越女剑的绝技施展出来，剑光闪烁，劲力到处，剑尖出现一道若隐若现的剑芒！\n"NOR,me);
      message_vision(HIY"长袖轻挥，身形随风而起，翩如惊鸿，婉若游龙，招式凌厉，宛如仙女。\n"NOR,me);
	  message_vision(HIW"阿青挺剑直刺，倏往倏来，长剑化成一道长虹，招招不离你的前胸，穿梭如飞，奔行如电！\n"NOR+
                     HIC"随手一剑刺向，出招平平无奇，去势却是绝快，直如流光破空，星丸跳跃！\n"NOR+
                     HIM"跃身半空，回剑下击，$w幻出无数个剑花，银光闪烁，宛如天河飞泻，空谷山崩！\n"NOR+
                     HIB"手中连连刺出，剑光有如浮光掠影,惊鸿翩逝,又似星丸跳跃,稍纵即逝！\n"NOR+
                     HIY"手捏剑诀，如青龙跃舞，铿然长吟,一道匹练般的剑芒迅疾迸射，疾刺而出！\n"NOR+
                     HIG"剑尖轻点，急射而出，幻出万千道剑影，将圈在其中，缭绕如虹，寒气大作！\n"NOR+
                     HIR"抱剑旋身，人剑合一，剑芒爆涨，纵横飞舞，进炸如雨！ \n"NOR+
                     HIB"随意一剑，光芒一闪而收，只觉那剑光迅疾逾电，迫在眉睫，唯有急速飞退！\n"NOR,me);

     if (i>=28 
		  && s==3
		  && t>200 //参悟20点解开
		  && j>40 )
		 {
	      command("smile");
	      command("say 你真是聪明伶俐，居然一下子就想明白了，比那个榆木疙瘩强多了。");
	      command("sigh");
	      command("say 他若像你这样聪明多好？");
    	  message_vision(HIC"随着阿青的一声长叹，神情终是郁郁，转身离去。\n一道若隐若无的声音传来，[人世间那得如意？还是好好珍惜当下吧。]\n"NOR,me);
           
          message_vision(HIR"\n\n恭喜你，经过阿青的指导，你对如何使用越女剑已经基本了解了，剩下的就是勤加练习了！\n"NOR,me);
          me->set("quest/ynj/pass","ok");
          me->set("title",HIC"越女剑"NOR);
		  me->set("mytitle/quest/yuenvtitle",HIC"越女剑"NOR);
		  me->set_skill("yuenu-jian",1);
          log_file("quest/yuenujian", sprintf("%s(%s) 恭喜！失败%d次成功解开越女剑。当前幸运值kar(KAR)：%d(%d),当前随机值：%d,当前随机悟性：%d(%d),当前随机total：%d(%d),当前经验：%d。\n", 
	      me->name(1),
          me->query("id"),
          me->query("quest/ynj/fail"),
		  i,
		  me->query("kar"),
		  s,
		  j,
		  me->query("int"),
		  t,
		  total,
          me->query("combat_exp")));
          me->start_busy(1);
		  return 1; 
	    }
     else
       {
          tell_object(me,HIG"\n你沉思许久，不得要领。\n"NOR);
          message_vision(HIC"\n$N摇了摇头，深深地叹了口气。\n"NOR,me); 
          tell_object(me,HBBLU"\n很可惜，你本次尝试越女剑秘密失败！\n"NOR);
          tell_object(me,HBBLU"你目前的经验是" + me->query("combat_exp") + "，现在时间是书剑"+ NATURE_D->game_time() + "，请记录。\n"NOR);
          tell_object(me,HBBLU"你将在间隔24小时后获得下一次机会！。\n\n"NOR);
				
		 log_file("quest/yuenujian", sprintf("%s(%s) 解越女剑失败%d次，当前幸运值kar(KAR)：%d(%d),当前随机值：%d,当前随机悟性：%d(%d),当前随机total：%d(%d),当前经验：%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/ynj/fail"),
		 i,
		 me->query("kar"),
		 s,
		 j,
		 me->query("int"),
		 t,
		 total,
         me->query("combat_exp")));
        
          me->start_busy(1);
          me->add("quest/ynj/fail",1);
          me->set("quest/ynj/exp", me->query("combat_exp") );
          me->start_busy(1);
          me->set("quest/ynj/time",time());
        }
     
    return 1;
}


// qqchi.c 裘千尺
// By River 99.5.25
#include <ansi.h>
inherit NPC;
string ask_dan();
string ask_quest();
string ask_tuzaohe();
string ask_pojie();

void create()
{
	set_name("裘千尺", ({ "qiu qianchi", "qiu", "qianchi"}));
	set("nickname", HIY"铁掌莲花"NOR);
	set("title",HIW"绝情谷女主人"NOR);
	set("long","一个半身赤裸的秃头婆婆盘膝坐在地下，满脸怒容，凛然生威。\n"); 
	set("gender", "女性");
	set("age", 55);
	set("attitude", "friendly");

	set("unique", 1);
	set("shen_type", -20);

	set("str", 35);
	set("int", 30);
	set("con", 28);
	set("dex", 5);
	set("per", 8);

	set("max_qi", 20000);
	set("max_jing", 20000);
	set("neili", 25000);
	set("max_neili", 25000);
	set("eff_jingli",20000);
	set("jiali", 200);
	set("combat_exp", 9500000);
	set("score", 20000);

	set_skill("force", 460);
	set_skill("guiyuan-tunafa", 460);
	set_skill("dodge", 460);
	set_skill("shuishangpiao", 460);
	set_skill("strike", 460);
	set_skill("tiezhang-zhangfa", 460);
	set_skill("parry", 450);
	set_skill("literate", 100);

	map_skill("force", "guiyuan-tunafa");
	map_skill("dodge", "shuishangpiao");
	map_skill("strike", "tiezhang-zhangfa");
	map_skill("parry", "tiezhang-zhangfa");
	prepare_skill("strike", "tiezhang-zhangfa");

	set("inquiry", ([ 
		"绝情丹" : (: ask_dan :),
		"公孙止" : (: ask_quest :),
		"破解金刀黑剑" : (: ask_pojie :),
		"吐枣核绝技" : (: ask_tuzaohe :)
	]));
	setup();
}

void kill_ob(object who)
{
	object me;
	object weapon;
	object ob;
	me=this_player();
	weapon = me->query_temp("weapon");
	ob=this_object();
	if (living(ob)) {
		command("sneer " + me->query("id"));
		if( weapon ){
			message_vision(HIW"$N突然波的一声，口中飞出一物 ，铮的一响，打在$n手中所握的那"+weapon->query("unit")+weapon->name()+HIW"上。\n"NOR,ob,me);
			weapon->move(environment(ob));
			me->add_busy(2);
			message_vision(HIR"\n$N只觉手臂剧震，五指竟然拿捏不住，当的一声，"+weapon->name()+HIR"落在地下。\n"NOR,me);
		}
		else {
			message_vision(HIW"$N口中枣核钉已疾射而出，破空之声有如尖啸，直指$n小腹，去势当真是悍猛无伦。\n"NOR,ob,me);
			me->add_busy(2);
			message_vision(HIR"\n$N“啊”的一声高叫，弯腰捧腹，俯下身去。\n"NOR,me);
			me->receive_damage("qi", me->query("eff_qi")/2);
			me->receive_wound("qi",  me->query("eff_qi") /2);
		}
	}
	::kill_ob(me);
}

string ask_dan()
{
	if(this_player()->query_temp("jqg/chi"))
		return "这位"+RANK_D->query_respect(this_player())+"，我不是已经告诉你，绝情丹所藏之处了么？";
	this_player()->set_temp("jqd/chi", 1);
		return "你我在此相遇亦算有缘，绝情谷唯一一颗绝情丹我藏在大厅第五块青砖下。";
}

string ask_quest()
{
	object me = this_player();

	if(me->query_temp("quest/jindao"))
		return "这位"+RANK_D->query_respect(this_player())+"，你还不去公孙止给我报仇，你是不是不想手发痒了？";
		
  if( me->query("combat_exp") < 2000000 )
        	return "以你当前的经验恐怕还不能替我报仇，还是抓紧去练功去吧。\n";
 
	me->set_temp("quest/jindaoheijian/jueqingdan", 1);
		return "哼，这恶贼害我到如此地步，不杀此贼我裘千尺誓不为人，你如果能将绝情丹找来，我就将告诉你一个秘密。";
}

int accept_object(object me, object ob)
{
	if( ob->query("id") == "jueqing dan" ) {
			command("sneer");
			tell_object(me,"20年前我大哥裘千丈被黄蓉害死了！\n");
			tell_object(me,"如果你能帮我去杀了黄蓉的话，hehe！\n");
			call_out("destructing", 1, ob); 
			me->set_temp("quest/jindaoheijian/jueqingdan",0);
			me->set_temp("quest/jindaoheijian/huangrong",1);
			return 1;
		  }
		else {
			command("say 居然拿假绝情丹来骗我,找死！");
			me->fight_ob(this_object());
			this_object()->kill_ob(me);
			me->set_temp("quest/jindaoheijian/jueqingdan",0);
			call_out("destructing", 1, ob); 
			return 1;
		     }
	return 1;
}
void destructing(object ob)
{
	if (ob) destruct(ob);
}


string ask_tuzaohe()
{
	object me=this_player();
	me->start_busy(10);
	
	if (me->query("quest/tiezhang/gytnf/pass"))
		return "你已经全部领悟了吐枣核绝技！\n";
	if (time()-me->query("quest/tiezhang/gytnf/time")<86400)
		return "你来的太勤快了！\n";
	if (me->query("family/family_name")!="铁掌帮")
		return "你不是铁掌帮弟子，来此作甚！\n";
	if (me->query_temp("quest/jindaoheijian/huangrong")) 
	{
		   message_vision(HIC"看在你救我出来并替我找到绝情丹的份上，我就告诉你这门绝技的奥秘，你附耳过来，我说与你听。\n"NOR,me);
		   command("say 吸纳百川归云海，鲸吞万里之势\n");
		   command("say 凝聚一线，勃然发力！\n");
           me->start_busy(999);
		   remove_call_out("thinking");
		   call_out("thinking",1,me);
		   me->delete_temp("quest/jindaoheijian/huangrong");
		   
	}else {
		message_vision(CYN"裘千尺嘿嘿冷笑几声，说道，你替我找回绝情丹再说。\n"NOR,me);
	}
	return "裘千尺冷冷地看了你一眼，目光中闪烁不定。\n";
}

int thinking(object me)
{
  int i,j; 
  if(!me) return 0;
  i=random(me->query("kar"));
  j=random(10);

  me->set("quest/tiezhang/gytnf/time",time());

  if (me->query("kar")>30) 
  {
	  log_file("quest/bug", sprintf("%s(%s) 参悟铁掌吐枣核绝技时，KAR异常，当前经验：%d。年龄：%d。kar:%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("combat_exp")),
		 me->query("age"),
		 me->query("kar"));
	  return 0;
  }
  if(me->query_temp("canwu_tuzaohe")<(15+random(10)))
   {  
	  me->add_temp("canwu_tuzaohe",1);

	  switch (random(9))
	  {
		case 0:
			tell_object(me,HIG"\n你将师傅所传授的心法彼此印证，只觉得耳目一新...\n"NOR);
			break;
		case 1:
			tell_object(me,HIY"\n忽然，你似乎抓住了一些明悟。\n"NOR);
			break;
		case 2:
			 tell_object(me,HIR"\n你陷入馄饨状态，大脑一片空明，似乎要抓住那个线索了！..\n"NOR);
			break;
		case 3:
			tell_object(me,HIW"\n你枯坐哪儿，甚是无聊，神情抑郁，似乎有些累了.\n"NOR);
			break;
		case 4:
			tell_object(me,CYN"\n你自言自语，神情疲倦之际，似乎遇到瓶颈了..\n"NOR);
			break;
		case 5:
			tell_object(me,MAG"\n你思维漂浮在空中，宛如婴儿沐浴.神清气爽.\n"NOR);
			break;
		default:tell_object(me,YEL"\n你叹了一口气，精神总是不能有效集中.\n"NOR);
			break;

	  }
      

	  tell_room(environment(me),HIC""+me->query("name")+"面色平和，浑然忘我，似乎在思索着什么...\n"NOR, ({}));
	
	  remove_call_out("thinking");
	  call_out("thinking",3+random(3), me);
	  return 1;

   } 
   else if (i>=25
			&& j<3
			&& me->query("kar")<31)
 	{ 
        
         me->start_busy(3);     
         message_vision(HIY"\n$N「哈哈哈」大笑几声，说道：“原来如此，原来如此。”\n"NOR,me); 
         message_vision(HIY"\n\n$N经过不断领悟，终于领悟了以内劲吐枣核的奥秘，归元吐纳法豁然贯通！”\n"NOR,me); 
         log_file("quest/tuzaohe", sprintf("%s(%s) 成功！第%d次参悟，机缘巧合下，成功参悟以归元气吐枣核的奥秘，当前幸运值：%d,当前随机值：%d,当前经验：%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/tiezhang/gytnf/fail"),
		 i,
		 j,
         me->query("combat_exp")));

		 me->set("quest/tiezhang/gytnf/time",time());
		 me->set("quest/tiezhang/gytnf/pass",1);
		 me->delete_temp("canwu_tuzaohe");
		 return 1;
     }
	 else {
	     message_vision(HIG"\n$N长叹一生，自言自语地说道：“看来又是一无所获啊。”\n"NOR,me); 
		 message_vision(HIY"\n参悟以气劲控制枣核的解密失败！\n"NOR,me); 
         log_file("quest/tuzaohe", sprintf("%s(%s) 失败！第%d次失败归元气劲吐枣核绝技，当前幸运值：%d,当前随机值：%d,当前经验：%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/tiezhang/gytnf/fail",1),
		 i,
		 j,
         me->query("combat_exp")));
        
		 me->add("quest/tiezhang/gytnf/fail",1);
		 me->set("quest/tiezhang/gytnf/time",time());
		 me->start_busy(2);
		 me->delete_temp("canwu_tuzaohe");
		 return 1;
   }

}

string ask_pojie()
{
	int i,j; 
	object me;
	me=this_player();
	  if(!me) return "";
	  i = 20;
    if(me->query("m-card-vip")) i =  18;
    if(me->query("y-card-vip")) i =  15;
    if(me->query("buyvip"))     i =  10;
    i=random(i);
	j=random(me->query("kar"));

    
	if (me->query("quest/tz/jdhj/pass"))
		return "你已经全部领悟了破解金刀黑剑奥秘！\n";
	if (time()-me->query("quest/tz/jdhj/time")<86400)
		return "你来的太勤快了！\n";
	if (me->query("family/family_name")!="铁掌帮")
		return "你不是铁掌帮弟子，来此作甚！\n";
	if (me->query("quest/jindaoheijian/pass")) 
	{
		   message_vision(HIC"看在你救我出来并替我找到绝情丹的份上，我就告诉你这门绝技的奥秘，你附耳过来，我说与你听。\n"NOR,me);
		   command("say 刀非刀，剑非剑，剑就是剑，刀就是刀。\n");
		   command("say 金刀黑剑此门武功只要沾染腥红之物毕被破解\n");
		   		   command("say 此武功难练易破，我当初就奉劝那个老鬼不要去练，可他就是不听\n");
		   		   command("say 既然他如此无情无义，那我就将这奥妙说给你听。\n");

		   me->delete_temp("quest/jindaoheijian/huangrong");
		   
	}else {
		message_vision(CYN"裘千尺嘿嘿冷笑几声，说道，你替我找回绝情丹再说。\n"NOR,me);
		return "裘千尺冷冷地看了你一眼，目光中闪烁不定。\n";

	 }

	  if (me->query("kar")>30) 
	  {
		  log_file("quest/bug", sprintf("%s(%s) 参悟铁掌吐枣核绝技时，KAR异常，当前经验：%d。年龄：%d。kar:%d。\n", 
			 me->name(1),
			 me->query("id"),
			 me->query("combat_exp")),
			 me->query("age"),
			 me->query("kar"));
		  return 0;
	  }
 
	  if ( i<3
	  && j>25
	  && random(me->query_int())>30
	  && me->query("kar")<31)
 	  { 
        
         me->start_busy(3);     
         message_vision(HIY"\n$N「哈哈哈」大笑几声，说道：“原来如此，原来如此。”\n"NOR,me); 
         message_vision(HIY"\n\n$N经过不断领悟，终于领悟了破解金刀黑剑的奥秘后豁然贯通！”\n"NOR,me); 
         log_file("quest/pojiejdhj", sprintf("%s(%s) 成功！失败%d次参悟后，机缘巧合下，成功参悟破解金刀黑剑的奥秘，当前幸运值：%d,当前随机值：%d,当前经验：%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/tz/jdhj/fail"),
		 j,
		 i,
         me->query("combat_exp")));

		 me->set("quest/tz/jdhj/time",time());
		 me->set("quest/tz/jdhj/pass",1);
		 return "哈哈哈·············我铁掌又增加一名高手！\n";
     }
 	 else {
	     message_vision(HIG"\n$N长叹一生，自言自语地说道：“看来又是一无所获啊。”\n"NOR,me); 
		 message_vision(HIY"\n参悟破解金刀黑剑的解密失败！\n"NOR,me); 
         log_file("quest/pojiejdhj", sprintf("%s(%s) 失败！第%d次失败破解金刀黑剑绝技，当前幸运值：%d,当前随机值：%d,当前经验：%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/tz/jdhj/fail",1),
		 j,
		 i,
         me->query("combat_exp")));

		 me->add("quest/tz/jdhj/fail",1);
		 me->set("quest/tz/jdhj/time",time());
		 me->start_busy(2);
		 return "真是晦气！\n";
   }

}


//flowray 2005.6.20
// By Spiderii@ty 加入限制，可以无限累加太变态了
#include <ansi.h>


inherit SPEC; 

void create()
{
	set_name (HIR"桃源罚恶令"NOR, ({ "faeling","ling"}));
	set("long","这是一面桃花源发出的罚恶令,你可以用他来惩戒("HIY"chengjie"NOR")杀害你的凶手。\n");

	set("unit","面");
	set_weight(100);
	set("value",3000000);
       set("no_give",1);
       set("no_drop",1);	
       set("no_get",1);

	set("degree",1);
	set("flag","spec/faeling");
	set("desc","可以用它惩戒杀害你的人。");
        set("credit",130);
	
	setup();
}

void init()
{
	add_action("do_chengjie","chengjie");
  
}

int do_chengjie(string arg)
{
	object where,ob,me=this_player();
	int i,j,last_on = strlen(arg);
	string id1,id2;    
	
	if (!arg)
      		{return notify_fail("你要惩戒谁?\n");}
      	else
      	{
        	while (last_on--) if (arg[last_on] < 'a' || arg[last_on] > 'z')
			{return notify_fail(arg+"是什么东东？\n");break;}
	}
	//加个限制,被杀一次，只能复仇1次 By Spiderii@ty
	if(me->query("last_killer")=="凶手已受惩戒")
		{ return notify_fail("凶手已受惩戒,得饶人处且饶人吧\n");}
	

	if(!objectp(ob = LOGIN_D->find_body(arg))) 
		{ return notify_fail("没有这个人在线。\n");}
	
	if(me->query("last_kzf")==arg)
		{ return notify_fail("你想恶人先告状？\n");}
	
	if(!(me->query("last_death_time/"+arg)))
      		{ return notify_fail("你只能惩戒杀害过你的人。\n");}
      	
      	// 追诉时限为一天
      	if (time()-me->query("last_death_time/"+arg)>86400)
      		{ return notify_fail("现在才来算这样的陈年老帐有点晚了吧。\n");}
      	i=strlen(arg)-1;
      	id1=capitalize(arg);
      	id2=capitalize(arg[0..0]+arg[i..i]);
      	if ((!strsrch(me->query("last_killer"),id1,1)) && (!strsrch(me->query("last_killer"),id2,1)))
      		{ return notify_fail("你只能惩戒这次杀害你的人。\n");}
      	
      	if (me->query("combat_exp")*1.5>ob->query("combat_exp"))
      		{ return notify_fail("怎么能凡事都求人,你还是努力点自己想办法解决吧。\n");}
      	
      	if (me->query("combat_exp")>2000000)
      		{ return notify_fail("怎么能凡事都求人,你还是努力点自己想办法解决吧。\n");}
      	
      	if (ob->query_condition("killer"))
      		{ return notify_fail("他现在正被官府通缉呢,你还是晚点再惩戒他吧。\n");}
      		

	if(!objectp(where = environment(ob)))
		  return notify_fail("这个人不知道躲在哪里耶... :-( \n");
	
	j=2*(ob->query("combat_exp")-me->query("combat_exp"))/me->query("combat_exp");
	j*=30;
	if (j>100) j=600; //适当延长时间,严打乱PK
	if (j<30) j=60;
	
	if (file_name(where) == "/d/wizard/relax") 
	{
		//ob->add_condition("relax", j*3);
		tell_object(me, (string)ob->query("name")+"现在正在惩戒当中。\n");
		//tell_object(ob,"你因为［持强凌弱］再次被人投诉,罪上加罪增加了"+chinese_number(j)+"分钟的禁闭时间。\n");
	}
	else	
	{
		tell_room(where, MAG"天空中飘落两位美貌仙女，扶起"+ob->query("name")+MAG"腾空而去了。\n"NOR, ({ ob }));
		tell_object(ob, MAG"两位美貌仙女出现在你眼前，扶着你缓缓飘了起来....\n"NOR);
		tell_object(ob,"你因为［持强凌弱］被人投诉,现决定给予关禁闭于桃花源"+chinese_number(j)+"分钟的处罚。\n");
		ob->apply_condition("relax", j*3);
		ob->move("/d/wizard/relax");
		ob->set("relax_timeout_room", file_name(where));	
		tell_object(me, (string)ob->query("name")+"受到惩戒,被抓到了桃花源禁闭"+chinese_number(j)+"分钟。\n");
		tell_room(environment(ob), MAG"两位仙女扶着"+ob->name()+MAG"飘来，将"+ob->name()+MAG"轻轻放在这里。\n"NOR, ({ ob }));
		ob->set("startroom", "/d/wizard/relax");
	}
	me->set("last_killer","凶手已受惩戒");
	degree();
	return 1;
}	 

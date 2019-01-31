// Room: /d/shaolin/fumoquan.c

#include <ansi.h>
inherit ROOM;
int do_kanshou(string arg);

void create()
{
	set("short", "金刚伏魔圈");
	set("long", @LONG
三棵大松树的树干上各挖了个可容身一人的大洞，有个洞口露出黑色僧
袍一角，似乎住得有人。中央是一片大草坪，下面有个洞(cave)，中心处光秃秃的，
似乎经常受大力击打，以致寸草不生。
LONG
	);

	set("exits", ([
		"out" : __DIR__"qyping",
	]));

	set("objects",([
		CLASS_D("shaolin") + "/du-nan" : 1,
		CLASS_D("shaolin") + "/du-e" : 1,
		CLASS_D("shaolin") + "/du-jie" : 1,
	]));
	set("item_desc", ([                    
         "cave": HIC"\n洞口为铁栅栏所封，洞下关押着魔教大魔头谢逊，少林正在为屠师大会做准备。\n"NOR,
     ]));

	set("outdoors", "少林寺");
	setup();
}

void init()
{
	mapping mine;
        object ob = this_player();
	mine = ob->query("family");
	
	add_action("do_kanshou","kanshou");

	if( !userp(ob) || wizardp(ob) ) return;
	if (ob->query("family/family_name") == "少林派" && (ob->query("passdu") || ob->query("pass_xin")))
		return;
	message_vision(HIR "突然间劲气纵横，三根黑索如三条黑蟒般就地滚来，瞬间近身，
化成一条笔直的兵刃，如长矛，如杆棒，如利剑，分别向$N的头，
胸，腹三处要害疾刺而至。$N一瞥间，看到三个老僧分居三个树
洞之中，正全力持鞭向$N攻来！$N已陷身于少林寺之蕴含无上降
魔大法的金刚伏魔圈！\n\n" NOR, ob);

	if ( mapp(mine)
	&& mine["generation"] > 36
	&& mine["family_name"] == "少林派"
	&& ob->query("qi") < 200 ){
		message_vision(HIR "$N被一道排山倒海般的劲气击中，顿时飞了出去！\n" NOR, ob);
		ob->move("/d/shaolin/qyping", 1);
		tell_room(environment(ob), ob->name()+"从伏魔圈飞了出来。\n", ob);
	}
}

int valid_leave(object me, string dir)
{

	if( dir == "out" && member_array("puti zi", deep_inventory(me)->query("id")) != -1 ) {
		return notify_fail("有个声音说道：不能带着菩提子离开伏魔圈 !\n");
	}
	if( dir == "out" && me->query_temp("ryb/askdue") ) {
		return notify_fail("渡厄说道：你刚答应我要替我看守谢逊，为何要离开伏魔圈 !\n");
	}

	me->delete_temp("fighter");
	return ::valid_leave(me, dir);
}

int do_kanshou(string arg)
{
	object me,weapon;
	int t;
	me=this_player();
	weapon=me->query_temp("weapon");
	t=6+random(10);
	
	if (!me->query_temp("ryb/askdue"))
	{
		return notify_fail("少林寺三渡和你无亲无故为啥要在此看守 !\n");

	}
	if (arg!="谢逊")
	{
		return notify_fail("渡厄说道：你磨磨蹭蹭在伏魔圈中干什么 !\n");

	}
	if (me->query_skill_mapped("whip")!="riyue-bian"
		||me->query_skill_mapped("parry")!="riyue-bian"
		||weapon->query("skill_type")!="whip")
	{
		return notify_fail("渡厄说道：你需要激发日月鞭方可和你叔叔们配合 !\n");

	}
	message_vision(HIC"渡厄大师说道，$N你要注意了，我听到有五个人向这边走来了,时间大约有"+chinese_number(t)+"秒！\n"NOR,me);

	call_out("mj_come1",t,me);
	return 1;

}
int mj_come1(object me)
{
	object leng,zhong,zhou,peng,budai;
	if (!objectp(leng=present("leng qian",environment(me))))
	{
		leng=new("kungfu/class/mingjiao/leng");
		leng->move(environment(me));
	}
	if (!objectp(zhong=present("zhang zhong",environment(me))))
	{
		zhong=new("kungfu/class/mingjiao/zhang2");
		zhong->move(environment(me));
	}	
	if (!objectp(peng=present("peng yingyu",environment(me))))
	{
		peng=new("kungfu/class/mingjiao/peng");
		peng->move(environment(me));
	}
	if (!objectp(zhou=present("zhou dian",environment(me))))
	{
		zhou=new("kungfu/class/mingjiao/zhou");
		zhou->move(environment(me));
	}
	if (!objectp(budai=present("shuo bude",environment(me))))
	{
		budai=new("kungfu/class/mingjiao/shuo");
		budai->move(environment(me));
	}

	message_vision(HIR"这时，忽然有五道人影倏然进入伏魔圈，喝道，“光明圣火，唯我明教“，大明教五散人来也！\n”"NOR,me);
	leng->kill_ob(me);
	zhong->kill_ob(me);
	zhou->kill_ob(me);
	peng->kill_ob(me);
	budai->kill_ob(me);
	call_out("mj_come2",10+random(10),me);
		message_vision(HIY"\n\n渡厄喊道，你动作要快点，我听到还有四个人正在向这奔来,这批高手比先前那五人更为厉害！\n"NOR,me);

	return 1;
}
int mj_come2(object me)
{
	object yin,zishan,fuwang;
	message_vision(HIY"忽然有人喊道，“熊熊烈火，焚我残躯” 明教四大法王来也！！\n"NOR,me);
	if (!objectp(yin=present("yin tianzheng",environment(me))))
	{
		yin=new("kungfu/class/mingjiao/yin");
		yin->move(environment(me));
	}
	yin->kill_ob(me);
	if (!objectp(zishan=present("dai qisi",environment(me))))
	{
		zishan=new("kungfu/class/mingjiao/dai");
		zishan->move(environment(me));
	}
	zishan->kill_ob(me);
	if (!objectp(fuwang=present("wei yixiao",environment(me))))
	{
		fuwang=new("kungfu/class/mingjiao/wei2");
		fuwang->move(environment(me));
	}
	fuwang->kill_ob(me);
	message_vision(HBYEL+HIW"\n\n\n渡厄叹息一声，面色忧虑，喊道，“我又听到有人来了，这次来的是两个高手”！！\n"NOR,me);
	call_out("mj_come3",15+random(10),me);
	return 1;
}
int mj_come3(object me)
{
	object yang,fan;
	message_vision(HIY"忽然有人喊道，“熊熊烈火，焚我残躯” 明教逍遥二仙来也！！\n"NOR,me);
	if (!objectp(yang=present("yang xiao",environment(me))))
	{
		yang=new("kungfu/class/mingjiao/yang");
		yang->move(environment(me));
	}
	yang->kill_ob(me);
	if (!objectp(fan=present("fan yao",environment(me))))
	{
		fan=new("kungfu/class/mingjiao/fan");
		fan->move(environment(me));
	}
	fan->kill_ob(me);
	message_vision(HBYEL+HIW"\n\n\n渡厄叹息一声，面色有些焦虑，喊道，“我又听到有人来了，这次来的是个超级高手”！！\n"NOR,me);
	call_out("mj_come4",15+random(10),me);
	return 1;
}
int mj_come4(object me)
{
	object zhang;
	message_vision(HIY"忽然有人喊道，“熊熊烈火，焚我残躯” 明教教主张无忌来也！！\n"NOR,me);
	if (!objectp(zhang=present("zhang wuji",environment(me))))
	{
		zhang=new("kungfu/class/mingjiao/zhangwuji2");
		zhang->move(environment(me));
	}
	zhang->kill_ob(me);
	me->set_temp("ryb/starttime",time());
	call_out("check_fight",20,me);
	message_vision(HIY"\n\n\n\n\渡厄喊道，再给你20秒时间，还不赶尽杀绝就算你任务失败！\n当然“要是实在撑不住就不要逞强了，安全第一”！！\n"NOR,me);
	
	return 1;
}

int check_fight(object me)
{
	int time;
	object due;
	//time=time()-me->query_temp("ryb/starttime");
	due=present("du e",environment(me));
	if (!me->is_living()
		||!me
		||!due
		||present("yang xiao",environment(me))
		||present("fan yao",environment(me))
		||present("zhang wuji",environment(me))
		||present("yin tianzheng",environment(me))
		||present("dai qisi",environment(me))
		||present("wei yixiao",environment(me)))
	{
		message_vision(HIW"伏魔金刚圈被破，谢逊为明教高手劫走，守护谢逊任务失败！\n"NOR,me);
		me->set("quest/sl/ryb/kanshou/time",time());
		me->delete_temp("ryb");
		return 1;
	}
	else {
	    message_vision(HIG"$N经过艰苦奋战，终于将魔教教徒杀干净！胜利完成渡厄交给自己的看守任务！\n"NOR,me);
		message_vision(HIY"\n\n渡厄高颂佛号，“南无阿弥陀佛”，善哉善哉！\n"NOR,me);
		due->do_say();
		me->set("quest/sl/ryb/kanshou/pass",1);
		me->delete_temp("ryb");

		return 1;
	}

}
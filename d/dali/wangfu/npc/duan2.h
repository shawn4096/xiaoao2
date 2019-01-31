// duan2.h
#include <ansi.h>
//#include TLS_QUEST_YYZ "";


string ask_helpwf()
{
    object me=this_player();
	//无量山找到段誉后情节
	if (me->query_temp("yyzhi/helpyuxu"))
	{
		return "多谢你解救了王妃。\n";
	}
	if (!me->query("quest/天龙八部/武功/yuxiang"))
	{
		return "誉儿据说在无量山一带，不知道他现在是否安全？真担心死我了。王妃的事先放一放。\n";
	}
	if (me->query("family/family_name")!="天龙寺")
	{
		return "你不是我天龙寺弟子来此作甚。\n";
	}
	if (me->query_skill("force",1)<300)
	{
		return "你的基本内功不足300，来了也帮不上忙。\n";
	}
	command("say 今日传闻四大恶人开始在大理国肆虐，我很担心王妃的安全。");
	command("consider ");
	command("say 你若有心就替我去一趟玉虚观，守住门口，千万不能让王妃受到伤害。\n");
	command("say 回来后我重重有赏。\n");
	me->set_temp("yyzhi/first",1);
    tell_object(me,HIC"段正淳在房间内走来走去，心神不宁，似乎有重大事情要发生似得。\n"NOR);
	return "段正淳长叹一声，道，“冤孽啊！”\n";

}
//第二步，需要找到段誉，解开无量山环节
string ask_helpmwq()
{
    object me=this_player();
	//无量山找到段誉后情节
	if (me->query_temp("yyzhi/helpmuover"))
	{
		return "多谢你解救了婉儿。\n";
	}
	if (!me->query_temp("yyzhi/helpyuxu"))
	{
		return "你连王妃都保护不好，还谈什么救助木婉清？\n";
	}
	if (me->query("family/family_name")!="天龙寺")
	{
		return "你不是我天龙寺弟子来此作甚。\n";
	}
	command("say 今日传闻四大恶人开始在襄阳城西一代追杀木婉清，我很担心她的安全。\n");
	command("say 据说不仅仅有四大恶人，其他不明江湖门派人士也加入其中，我甚是担心。\n");
	command("say 当年之事感慨万千，你若替我找回婉儿，我定当厚报.\n");
	command("sigh ");
	command("say 你若有心办此事，就替我去皇宫找皇后要一重要物品，那是婉儿之物，她一看即知。\n");
	me->set_temp("yyzhi/findqueen",1);
	me->delete_temp("yyzhi/helpwf");
    tell_object(me,HIC"段正淳在房间内走来走去，心神不宁，似乎有重大事情要发生似得。\n"NOR);
	return "段正淳似乎面色有些尴尬，不住搓手。\n";

}
//第三步，救甘宝宝
string ask_helpgbb()
{
    object me=this_player();
	if (me->query_temp("yyzhi/helpgbbover"))
	{
		return "多谢你解救了宝宝。\n";
	}
	if (!me->query_temp("yyzhi/helpmuover"))
	{
		return "你连婉儿都保护不好，还谈什么救助我的宝宝？\n";
	}
	command("say 今日传闻四大恶人开始在威胁我的宝宝，我很担心她的安全。\n");
	command("say 当年之事感慨万千，现在正是多事之秋，你若替我保护好宝宝，我定当厚报.\n");
	command("sigh ");
	command("say 你若有心就替我去到万劫谷去替我问候下我的宝宝。\n");
	me->set_temp("yyzhi/helpgbb",1);
	me->delete_temp("yyzhi/helpmuover");
    tell_object(me,HIC"段正淳在房间内走来走去，心神不宁，似乎有重大事情要发生似得。\n"NOR);
	return "段正淳面色尴尬，不住搓手。\n";

}
//第四步，救护秦红棉
string ask_helpqhm()
{
    object me=this_player();
	if (me->query_temp("yyzhi/helpqhmover"))
	{
		return "多谢你解救了我的棉棉。\n";
	}
	if (!me->query_temp("yyzhi/helpgbbover"))
	{
		return "你连我的宝宝都保护不好，还谈什么救助我的棉棉？\n";
	}
	command("say 今日传闻四大恶人开始在威胁我的棉棉，我很担心她的安全。\n");
	command("say 当年之事感慨万千，现在正是多事之秋，你若替我保护好棉棉，我定当厚报.\n");
	command("sigh ");
	command("say 你若有心就替我去到无量剑派去替我问候下我的棉棉。\n");
	me->set_temp("yyzhi/helpqhm",1);
	me->delete_temp("yyzhi/helpmuover");
    tell_object(me,HIC"段正淳在房间内走来走去，心神不宁，似乎有重大事情要发生似得。\n"NOR);
	return "段正淳面色尴尬，不住搓手。\n";

}


//第五步 拈花寺大战
string ask_helpnhs()
{
    object me=this_player();
	if (me->query_temp("yyzhi/helnhsmover"))
	{
		return "多谢你替我请来拈花寺黄眉大师。\n";
	}
	if (!me->query_temp("yyzhi/helpqhmover"))
	{
		return "你连棉棉都保护不好，还谈什么替我去请人？\n";
	}
	command("say 今日听说四大恶人开始在威胁我大理安危，我替我到大理城东拈花寺一趟。\n");
	command("say 当年之事感慨万千，现在正是多事之秋，你若替我请来黄眉大师，我定当厚报.\n");
	command("sigh ");
	command("say 有了黄眉大师的加入，对付四大恶人就心中有数了。\n");
	me->delete_temp("yyzhi");
	me->set_temp("yyzhi/helpnhs",1);
	
    tell_object(me,HIC"段正淳在房间内走来走去，心神不宁，似乎有重大事情要发生似得。\n"NOR);
	return "段正淳心事重重。\n";

}

/*

int accept_object(object who, object obj)
{
	
	//云中鹤
	if (who->query_temp("yyzhi/helpyuxu")&& obj->query("id")=="shouji"&&obj->query("name")=="云中鹤的首级")
	{
		who->delete_temp("yiyangzhi/helpyuxu");
		who->set_temp("yiyangzhi/duan2",1);
		tell_object(who,HIY"段正淳见到这枚云中鹤的首级，似乎对你的好感大增。\n"NOR);
        command("laugh ");
		obj->move(this_object());
		destruct(obj);
		message_vision(HIC"段正淳顺手从口袋里掏出一个金锭给你，说道，”拿去喝酒去吧“\n"NOR,who);
		who->add("combat_exp",random(2000));
		new("clone/money/gold")->move(this_object());
		message_vision(HIC"你的经验增加了！\n"NOR,who);
		command("give 1 gold to "+who->query("id"));
		return 1;
	}
	
	//南海鳄神
	if (who->query_temp("yyzhi/helpmuover")&& obj->query("id")=="shouji"&&obj->query("name")=="南海鳄神的首级")
	{
		who->delete_temp("yyzhi/helpmuover");
		who->set_temp("yyzhi/send/over",1);
		write(HIY"段正淳见到这枚南海鳄神的首级，对你甚是满意，似乎对你的好感大增。\n"NOR);
        command("laugh ");
		obj->move(this_object());
		destruct(obj);
		message_vision(HIC"段正淳顺手从口袋里掏出一个金锭给你，说道，”拿去喝酒去吧“\n"NOR,who);
		who->add("combat_exp",random(2000));
		new("clone/money/gold")->move(this_object());
		message_vision(HIC"你的经验增加了！\n"NOR,who);
		command("give 1 gold to "+who->query("id"));
		return 1;
	}
	//钟万仇
	if (who->query_temp("yyzhi/three/ganover")&& obj->query("id")=="shouji"&&obj->query("name")=="钟万仇的首级")
	{
		who->delete_temp("yyzhi/three/ganover");
		who->set_temp("yyzhi/three/over",1);
		write(HIY"段正淳见到这枚钟万仇的首级，对你甚是满意，似乎对你的好感大增。\n"NOR);
        command("laugh ");
		obj->move(this_object());
		destruct(obj);
		message_vision(HIC"段正淳顺手从口袋里掏出一个金锭给你，说道，”拿去喝酒去吧“\n"NOR,who);
		who->add("combat_exp",random(2000));
		new("clone/money/gold")->move(this_object());
		message_vision(HIC"你的经验增加了！\n"NOR,who);
		command("give 1 gold to "+who->query("id"));
		return 1;
	}
	//叶二娘
	if (who->query_temp("yyzhi/four/askhuang")&& obj->query("id")=="shouji"&&obj->query("name")=="叶二娘的首级")
	{
		who->delete_temp("yyzhi/four/askhuang");
		who->set_temp("yyzhi/four/over",1);
		write(HIY"段正淳见到这枚叶二娘的首级，对你甚是满意，似乎对你的好感大增。\n"NOR);
        command("laugh ");
		obj->move(this_object());
		destruct(obj);
		message_vision(HIC"段正淳顺手从口袋里掏出一个金锭给你，说道，”拿去喝酒去吧“\n"NOR,who);
		who->add("combat_exp",random(2000));
		new("clone/money/gold")->move(this_object());
		message_vision(HIC"你的经验增加了！\n"NOR,who);
		command("give 1 gold to "+who->query("id"));
		return 1;
	}
	//段延庆
	if (who->query_temp("yyzhi/five/..")&& obj->query("id")=="shouji"&&obj->query("name")=="叶二娘的首级")
	{
		who->delete_temp("yyzhi/four/askhuang");
		who->set_temp("yyzhi/four/over",1);
		write(HIY"段正淳见到这枚叶二娘的首级，对你甚是满意，似乎对你的好感大增。\n"NOR);
        command("laugh ");
		obj->move(this_object());
		destruct(obj);
		message_vision(HIC"段正淳顺手从口袋里掏出一个金锭给你，说道，”拿去喝酒去吧“\n"NOR,who);
		who->add("combat_exp",random(2000));
		new("clone/money/gold")->move(this_object());
		message_vision(HIC"你的经验增加了！\n"NOR,who);
		command("give 1 gold to "+who->query("id"));
		return 1;
	}



}*/
// Write by look
// Modify by bbb
// Modify by snowman@SJ 17/02/2000
// check leitaiuser.

#include <ansi.h>
#include <login.h>
#define SYNTAX  "指令格式：catch <某人> because <原因> <分钟>\n"

inherit F_CLEAN_UP;


int main(object me, string str)
{
	object ob, where;
	int times;
	string name, reason;
	mapping note;
	
	if(!str || sscanf(str, "%s because %s %d", name, reason, times)!=3 )
		  return notify_fail(SYNTAX);

	if (!objectp(ob = LOGIN_D->find_body(name)))
		  return notify_fail("这个...这个... 有这个人吗?\n");

	if (wiz_level(ob))
		  return notify_fail("对方是共同奋斗的战友噢，你这样做不太好吧？\n");

	if (!objectp(where = environment(ob)))
		  return notify_fail("这个人不知道躲在哪里耶... :-( \n");

	if (file_name(where) == RELAX_ROOM)
		  return notify_fail("他已经在桃花源思过了，不用再抓了。\n");

	if (base_name(ob) == "/d/xiangyang/leitai/npc/leitaiuser")
		return notify_fail(ob->name() + "这人是比武擂台Clone出来的，在擂台内让他离开就是了。\n");

	tell_room(where, MAG"天空中飘落两位美貌仙女，扶起"+ob->query("name")+MAG"腾空而去了。\n"NOR, ob);
	tell_object(ob, MAG"两位美貌仙女出现在你眼前，扶着你缓缓飘了起来....\n"NOR);

	tell_object(ob, "您因为［" + reason + "］，违反书剑游戏规则，决定给予关禁闭于桃花源" + CHINESE_D->chinese_number(times) + "分钟的处罚。\n"
	);

	message("channel", HIC "\n【纪律】"+ob->query("name")
		+"("+capitalize(ob->query("id"))
		+")因为［" + reason + "］，违反书剑游戏规则，决定给予关禁闭"
		"于桃花源" + CHINESE_D->chinese_time(times*60) + "的处罚。\n\n" NOR, users()
	);
	
	note = (["title":"禁闭玩家"+ob->query("name")
		+"("+capitalize(ob->query("id"))
		+")处理公告",
		"author":me->query("name") + "(" + getuid(me) + ")",
		"time":0,
		"msg":0,]);
	"/clone/board/wizto_b"->done_post(this_object(),note,"【纪律】"+ob->query("name")
		+"("+capitalize(ob->query("id"))
		+")因为［" + reason + "］，违反书剑游戏规则，决定给予关禁闭"
		"于桃花源" + CHINESE_D->chinese_time(times*60) + "的处罚。\n");
		
	//处罚公开，POST专门留言板
	/*
	"/clone/board/wizto_b"->auto_post("禁闭玩家"+ob->query("name")
		+"("+capitalize(ob->query("id"))
		+")处理公告","【纪律】"+ob->query("name")
		+"("+capitalize(ob->query("id"))
		+")因为［" + reason + "］，违反书剑游戏规则，决定给予关禁闭"
		"于桃花源" + CHINESE_D->chinese_time(times*60) + "的处罚。\n");
	*/
			
	ob->add_condition("relax", times*3);
	ob->set("relax_timeout_room", file_name(where));
	ob->move(RELAX_ROOM);

	tell_object(me, "你把"+ob->query("name")+"抓到了桃花源。\n");
	tell_room(environment(ob), MAG"两位仙女扶着"+ob->name()+MAG"飘来，将"+ob->name()+MAG"轻轻放在这里。\n"NOR, ob);

	log_file("static/CATCH",
		sprintf("%s 因为 [%s] 被 %s(%s) 抓到桃花源。禁闭时间 %d 分钟。\n",
			name, reason, (string)me->query("name"),me->query("id"), times
		), ob, ({ me })
	);

	return 1;
}

string query(string arg)
{
	if(arg=="id") //return now_id;
	return "Wizard";
}


int help(object me)
{
write(@HELP
指令格式 : catch <某人> because <原因> <分钟>

此指令可让你将某个违反规则的玩家移送到桃花源。
禁闭时间到后自动释放。
犯规次数自动累加。
HELP
    );
    return 1;
}

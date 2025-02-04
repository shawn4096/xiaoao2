// name.c

// Modified by mxzhao 2004/04/15 for group title

#include <ansi.h>
#include <dbase.h>
#include <condition.h>

nosave string *my_id;

void set_name(string name, string *id)
{
	set("name", name);
	set("id", id[0]);
	my_id = id;
}

int id(string str)
{
	string *applied_id, suffix;
	int i = 0;
	object me, env, ob = this_object();

	if ((me = this_player()) && !me->visible(ob)) return 0;

	reset_eval_cost();
	if (arrayp(applied_id = query_temp("apply/id")) && member_array(str, applied_id) != -1) return 1;

	// If apply/id exists, this object is "pretending" something, don't
	// recognize original id to prevent breaking the pretending with "id"
	// command.

	if (arrayp(my_id) && member_array(str, my_id) != -1) return 1;

	if (me && stringp(str)) {
		sscanf(str, "%d%s", i, suffix);
		if (sizeof(suffix)) i = 0;
		if (i > 0 && (env = environment()) && clonep(env)) {
			foreach (object item in all_inventory(env)) {
				if (!me->visible(item)) continue;
				if (!i--) break;
				if (item == ob) {
					if (!i) return 1;
					break;
				}
			}
		}
	}
	return 0;
}

string *parse_command_id_list()
{
	string *applied_id;

	if (arrayp(applied_id = query_temp("apply/id"))
	&& sizeof(applied_id))
		return applied_id;

	return my_id;
}

varargs string name(int raw)
{
	object me = this_object();
	object ob = this_player();
	string str, *mask;

	if( !raw && sizeof(mask = query_temp("apply/name")) )
		return mask[sizeof(mask)-1];
	if (!raw && wizardp(me))
		if (intp(query("env/invisibility"))
		&& query("env/invisibility") > 0)
			if ((ob && !ob->visible(me)) || ob==me) return "某人";
			else return "隐身的"+query("name");
	if( stringp(str = query("name")) )
		return str;
	return file_name(me);
}

varargs string short(int raw)
{
	object me = this_object();
	string force;
	mapping msg;
	string str, *mask;
	string title1,title2;

	if( !stringp(str = query("short")) )
	if (query("color")) str = query("color") + name(raw) + NOR "(" + capitalize(query("id")) + ")";
	else str = name(raw) + "(" + capitalize(query("id")) + ")";

	if (!me->is_character()) return str;

	if (!raw && sizeof(mask = query_temp("apply/short"))) str = mask[sizeof(mask)-1];
	else {
		string title, nick;

		if (stringp(nick = query("nickname"))) nick = "「" + nick + "」";
		
		// Modified by mxzhao 2004/04/15
		if (stringp(query("group/id")))
		{
			title1 = GROUP_D->get_group_name(query("group/id"), 1);
			title2 = GROUP_D->get_member_class(query("group/id"), query("group/class"));
			title = title1 + title2;
			set_temp("title", title);
	}
	if (!stringp(title) 
			&& !stringp(title = query_temp("title")) 
			&& !stringp(title = query("title")))
		//if (!stringp(title = query_temp("title")) && !stringp(title = query("title")))
		// End
		{
			title = "";
			if (!nick) nick = "";
		}
		else if (!nick) nick = " ";
		
		str = title + nick + str;
	}

	if (!raw) {
		if (query_temp("pending/exercise")) {
			force = me->query_skill_mapped("force");
			if (force) msg = SKILL_D(force)->exercise_msg(me);
			if (!msg || undefinedp(msg["status_msg"])) str = name() + "正在修炼内力";
			else str = msg["status_msg"];
		}
		else if (query_temp("pending/respirate")) str = name() + "正在吐纳炼精";
		else if (query_temp("pending/heal")) str = name() + "正在运功疗伤";
		else if (query_temp("pending/lingwu")) str = name() + "正在领悟武学";
		else if (query_temp("pending/duanzao")) str = name() + "正在锻造武器";
		else if (query_temp("pending/zhizao")) str = name() + "正在织造护具";
	}

	if (!raw || wiz_level(me)) {
		if (me->is_ghost()) str = HIB "(鬼气) " NOR + str;
		if (me->query("no_pk")) str = HIY "(退隐江湖) " NOR + str;
		if (userp(me) && me->query_condition("killer")){
			if( me->query_condition("pk") ) str = HIR "(杀人犯) " NOR + str;
			else str = RED "(通缉犯) " NOR + str;
		}
		if (raw = query_temp("netdead")) str += HIG " <断线" + CHINESE_D->chinese_time(uptime() - raw) + ">" NOR;
		if (in_input()) str += HIC " <输入文字中>" NOR;
		if (in_edit()) str += HIY " <编辑档案中>" NOR;
		if (interactive(me) &&  query_idle( me ) > 120) str += HIM " <发呆" + CHINESE_D->chinese_time(query_idle(me)) + ">" NOR;
		if (me->is_fighting()) str += HIR " <战斗中>" NOR;
		if (stringp(force = query("disable_type"))) str += HIR + force + NOR;
		if (query_temp("pending/swimming")) str += GRN" <游水中>"NOR;
	}

	return str;
}

varargs string long(int raw)
{
	string str, extra, *mask;

	if( !raw && sizeof(mask = query_temp("apply/long")) )
		str = mask[<1];
	else {
		if( !stringp(str = query("long")) )
			str = short(1) + "\n";
		else str = short(1) + "\n" + str;
	}

	if( stringp(extra = this_object()->extra_long()) )
		str += extra;

	return str;
}


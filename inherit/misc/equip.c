// equip.c

inherit ITEM;
inherit F_EQUIP;

int is_owner(object me)
{
	if(!me) return 0;		
	if( query("owner") == getuid(me) ) return 1;	
	return 0;
}

void setup()
{
	if (!clonep()) {
		if (query("armor_type"))
			add("armor_prop/dodge", - weight() / 2500 );
		if (query("weapon_type"))
			add("weapon_prop/dodge", - weight() / 2500 );
	}
}

nosave int use_flag = 1;
nosave object *buf = ({ });

void hit_ob(object me, object victim)
{
	if (use_flag < 2 && me->query("combat_exp") / 4 < victim->query("combat_exp") / 3) {
		buf -= ({ 0 });
		if (member_array(victim, buf) < 0) {
			buf += ({ victim });
			use_flag++;
		}
	}
}

void ob_hit()
{
	if (use_flag < 2)
		use_flag++;
}

void reset()
{
	object env = environment();

	switch (query("armor_type")) {
		case 0:
		case "armor":
		case "cloth":
			break;
		default:
			return;
	}
	
	if (!env || !userp(env) || use_flag--)
		return;

	if (query("unique")) {
		//增加 不洗手的贵宾卡会员武器不掉
		if (env->query("registered") >= 3 && !env->query("no_pk"))
			return;

		message_vision("$N一时想不起"+query("name")+"有什么用处，就随手把它丢掉了。\n", env);
		destruct(this_object());
	}
}

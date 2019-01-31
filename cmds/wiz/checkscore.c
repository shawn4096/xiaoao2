// create by yixian@xjkx2000

#include <ansi.h>
#include <combat.h>

int main()
{
	object *ob;
	object weapon;
	string msg, skill_type, COR;
	int i, attack_points, dodge_points, parry_points;

	ob = users();
	ob = filter_array(ob,(: !wizardp($1) && environment($1) :));

	msg = HIC"Íæ¼Ò¹¥»÷Á¦ÁÐ±í£º"NOR"\n";
	i = sizeof(ob);

	while (i--) {
		if (objectp(weapon = ob[i]->query_temp("weapon")) ) skill_type = weapon->query("skill_type");
		else {
			mapping prepare = ob[i]->query_skill_prepare();

			if (!sizeof(prepare)) skill_type = "unarmed";
			else skill_type = keys(prepare)[0];
		}

		attack_points = COMBAT_D->skill_power(ob[i], skill_type, SKILL_USAGE_ATTACK);
		parry_points = COMBAT_D->skill_power(ob[i], "parry", SKILL_USAGE_DEFENSE);
		dodge_points = COMBAT_D->skill_power(ob[i], "dodge", SKILL_USAGE_DEFENSE);
		if (attack_points > (int)ob[i]->query("combat_exp")*15)
		{
			COR = HBYEL;
		}
		else{
			COR = "";
		}
		msg += sprintf("%s%-10s %-20s "HIY"¹¥»÷£¨ÉËº¦£©£º%-10s ( %-6s )"HIY" ÕÐ¼Ü£º"HIG"%-10d "HIY" ¶ãÉÁ£¨·ÀÓù£©£º"HIG"%-10d ( %-6d )"NOR"\n",
			COR,
			ob[i]->query("family/family_name") == 0 ? "["HIC"ÆÕÍ¨°ÙÐÕ"+NOR+COR+"]" : "["HIC+ob[i]->query("family/family_name")+NOR+COR+"]",
			ob[i]->query("name")+"("+ob[i]->query("id")+")",
			attack_points > (int)ob[i]->query("combat_exp")*15 ? (HIR+attack_points/100+NOR+COR) : (HIG+attack_points/100+NOR+COR),
			ob[i]->query_temp("apply/damage") > 500 ? (HIR+ob[i]->query_temp("apply/damage")+NOR+COR) : (HIW+ob[i]->query_temp("apply/damage")+NOR+COR),
			parry_points/100,
			dodge_points/100,
			ob[i]->query_temp("apply/armor")
		);
	}
         
	msg += "\n\n";
	this_player()->start_more(msg);
	return 1;
}


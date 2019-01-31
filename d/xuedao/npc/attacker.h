// attacker.h for hs job
int do_copy(object me);

int do_copy(object me)
{
        object ob, weapon;
        string my_id, type, type1;
        int i;
        ob = this_object();

        if(!me) ob->unconcious();
        my_id = me->query("id");
        weapon = ob->query_temp("weapon"); 
          
        i = me->query("max_pot") - 100;
		if (me->query("combat_exp")<800000)
		{
			i=i-30;
		}else if (me->query("combat_exp")<1000000)
		{
			i=i-20;
		}
		else if (me->query("combat_exp")<1500000)
		{
			i=i-10;
		}else i=i;

        if(i < 120) i = 120;

        ob->set("combat_exp", (int)me->query("combat_exp"));
        if(weapon) {
           type = weapon->query("skill_type");
           type1 = ob->query_skill_mapped(type);
           ob->set_skill(type, i);
           ob->set_skill(type1, i);
        }
        ob->set_skill("force", i);
        ob->set_skill("cuff", i);
        ob->set_skill("dodge", i);
        ob->set_skill("parry", i);
        ob->set_skill(ob->query_skill_mapped("dodge"), i);
        ob->set_skill("xinyuegong", i);  
        ob->set_skill("yinyun-ziqi", i);     
        ob->set_skill("taizu-quan", i); 
        ob->set("max_qi", me->query("max_qi")/3*2); 
        ob->set("max_jing", me->query("max_jing")/3*2); 
        ob->set("max_neili", me->query("max_neili")/3*2);
        ob->set("jiali", ob->query_skill("force")/3);
        ob->reincarnate(); 
        ob->set("eff_jing", me->query("eff_jing")/3*2);
        ob->set("eff_jingli", me->query("jingli")/3*2);
        ob->set("max_neili", me->query("max_neili")/3*2);
		ob->set("neili", me->query("max_neili"));
        ob->set("eff_qi", me->query("max_qi")*2);
        command("stare " + me->query("id"));
        command("say "+me->query("name")+"乃是武林淫贼，邪恶无比，人人得而诛之。" );
		ob->set("victim", me->query("id"));
        remove_call_out("checking");
		call_out("checking",1,me,ob);
		return 1;
}
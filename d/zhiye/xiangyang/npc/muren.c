// /d/xiangyang/muren.c ľ��

inherit NPC;

int do_turn(string arg);
int do_get(string arg);

void create()
{
	set_name("ľ��", ({ "mu ren", "mu", "ren", "wood man", "wood", "muren" }) );
	set("gender", "����" );
	set("age", 30);
	set("mute", 1);
	set("long", "һ���������ɵ�ľ�ˣ�������ѡ���ϵȺ�ľ��\n"
	"�ؽڴ���ϸС��ͭ��í�ϣ��Եü�Ϊ��\n"
	"ͷ�����������Բľ�������ɣ�����������\n"
	"���Ҳ�����ܷ������������ڱ�����һ��СС�Ŀ���(trigger)��\n");
	set("attitude", "friendly");

	set("str", 25);
            set("no_quest", 1);
	set("cor", 25);
	set("cps", 25);
	set("int", 25);

	set("max_qi", 300);
	set("eff_qi", 300);
	set("qi", 300);
	set("max_jing", 100);
	set("jing", 100);
	set("neili", 300);
	set("max_neili", 300);
	set("jiali", 10);
	set("shen_type", 0);

	set_weight(10000);
	set("material", "wood");
	set("combat_exp", 50000);

	set_skill("force", 30); 
	set_skill("unarmed", 30);
	set_skill("dodge", 30);
	set_skill("parry", 30);

	set("fight_times", 0);	
	set("owner", this_object());

	setup();
}

void init()
{
	if (query("destructing")) return;
	add_action("do_get", "get");
	add_action("do_turn", ({"turn", "ban"}));
	if (!objectp(query("owner"))) {
		set("destructing", 1);
		set_ghost(1);
		call_out("destruct_me", 1);
	}
}

void destruct_me()
{
	destruct(this_object());
}

void unconcious()
{
	object me = this_object();

	this_player()->add_temp("muren_num", -1);
	say("ľ�˺�Ȼ������������һ�����죬í�ڹؽڴ���ͭ����������������\n"
	"��������ɢ���ˣ����ҵ�����һ�ء�\n");
	new("/d/xiangyang/obj/mutou")->move(environment(me));
	destruct(me);
}

void die()
{
	unconcious();
}

int accept_fight(object ob)
{
	return notify_fail("������㣬��ֻ�Ǹ�ľ�˶��ѣ�\n");
}

int do_get(string arg)
{
	object npc = this_object();
	object me = this_player();

	if (!arg) return notify_fail("��Ҫ����ʲô������\n");
	if (npc != present(arg, environment())) return 0;
	if (environment() == me) {
		write("�㲻���Ѿ���������\n");
		return 1;
	}
	if (query("owner") != me) {
		write("��������㶩����ľ�ˣ�\n");
		return 1;
	}
	if (is_busy() || is_fighting()) {
		write("ľ��������ս�����޷���������\n");
		return 1;
	}
	if (npc->move(me)) {
		if (me->is_fighting()) me->start_busy(1);
		message_vision( "$N��$n�����˱��ϡ�\n", me, npc);
		return 1;
	}
	else {
		write("���޷�����ľ�ˣ�\n");
		return 1;
	}
	return 0;
}


int do_turn(string arg)
{
	object me = this_object();
	object ob = this_player();
	mapping hp_status, skill_status, map_status, prepare_status;
	string *sname, *mname, *pname;
	int i, temp;

	if (ob->is_busy()) return notify_fail("����æ���أ�\n");
	if (arg != "trigger" && arg != "kaiguan") return notify_fail("��Ҫ�⶯ʲô��\n");
	if (query("owner") != ob) return notify_fail("�㷢�ֿ����ƺ���ʲô������ס�ˣ���ô�ⶼ�ⲻ����\n");

//	if (ob->is_fighting()) return notify_fail("����æ�Ŵ���أ�\n");
	if (is_fighting()) return notify_fail("ľ�������Զ���ս�����޷��������أ�\n");

	if (environment() == ob) return notify_fail("�Ȱ�ľ�˷�������˵�ɣ�\n");
	if (environment(ob) != environment()) return notify_fail("�㹻����ľ�˵Ŀ��أ�\n");
	if (environment()->query("no_fight")) return notify_fail("���ﲻ׼��ܣ�\n");

	message_vision("$N����ذ⶯��ľ�˱���Ŀ��ء�\n", ob);	
	add("fight_times", 1);

/* delete and copy skills */

	if ( mapp(skill_status = me->query_skills()) ) {
		skill_status = me->query_skills();
		sname  = keys(skill_status);

		temp = sizeof(skill_status);
		for(i=0; i<temp; i++) {
			me->delete_skill(sname[i]);
		}
	}

	if ( mapp(skill_status = ob->query_skills()) ) {
		skill_status = ob->query_skills();
		sname  = keys(skill_status);

		for(i=0; i<sizeof(skill_status); i++) {
			me->set_skill(sname[i], skill_status[sname[i]]);
		}
	}
	
/* delete and copy skill maps */

	if ( mapp(map_status = me->query_skill_map()) ) {
		mname  = keys(map_status);

		temp = sizeof(map_status);
		for(i=0; i<temp; i++) {
			me->map_skill(mname[i]);
		}
	}

	if ( mapp(map_status = ob->query_skill_map()) ) {
		mname  = keys(map_status);

		for(i=0; i<sizeof(map_status); i++) {
			me->map_skill(mname[i], map_status[mname[i]]);
		}
	}
	
/* delete and copy skill prepares */

	if ( mapp(prepare_status = me->query_skill_prepare()) ) {
		pname  = keys(prepare_status);

		temp = sizeof(prepare_status);
		for(i=0; i<temp; i++) {
			me->prepare_skill(pname[i]);
		}
	}

	if ( mapp(prepare_status = ob->query_skill_prepare()) ) {
		pname  = keys(prepare_status);

		for(i=0; i<sizeof(prepare_status); i++) {
			me->prepare_skill(pname[i], prepare_status[pname[i]]);
		}
	}
	
	hp_status = ob->query_entire_dbase();

	set("str", hp_status["str"]);
	set("int", hp_status["int"]);
	set("con", hp_status["con"]);
	set("dex", hp_status["dex"]);

	set("max_qi",    hp_status["max_qi"]);
	set("eff_qi",    hp_status["eff_qi"]);
	set("qi",        hp_status["qi"]);
	set("max_jing",  hp_status["max_jing"]);
	set("eff_jing",  hp_status["eff_jing"]);
	set("jing",      hp_status["jing"]);
	set("max_neili", hp_status["max_neili"]);
	set("neili",     hp_status["neili"]);
	set("jiali",     hp_status["jiali"]);
	set("combat_exp",hp_status["combat_exp"]);

	message_vision("ľ�˺�ȻһԾ���𣬶�$N���������ҵĽ�����\n", ob);	
	me->fight_ob(ob);
	ob->fight_ob(me);
	return 1;
}

void kill_ob(object ob)
{
	ob->remove_killer(this_object());
	remove_killer(ob);
	write("������㣬��ֻ�Ǹ�ľ�˶��ѣ�\n");
}

int remove_enemy(object ob)
{
	if (query("fight_times") >= 30) {
		unconcious();
		return 1;
	}

	return ::remove_enemy(ob);
}
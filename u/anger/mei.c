// mei.c ÷����
// Modified by Darken/Numa@SJ for taohua quest
//���Ӿ����׹�צ������� by renlai
#include <ansi.h>
inherit NPC;
string jybgz();
void create()
{
	set_name( "÷����" ,({ "mei chaofeng", "mei" }));
	set("title", "�ڷ�˫ɷ");
	set("nickname", HIB"��ʬ"NOR);
	set("gender", "Ů��");
	set("age", 32);
	set("long",
		"÷�����ǻ�ҩʦΨһ��Ů���ӣ��������ܻ�ҩʦ�۰�����ϧ����ʦ�ֳ�����\n"
		"������㺣�����͵�ˡ������澭�¾�˽����\n"
		"����ɫ�����Ϊ�þӺ����Ե���ڣ�ģ��ȴ��Ϊ�����������һ��������Ⱦ�ͨ�޷���\n");
	set("attitude", "aggressive");

        set("str", 47);
        set("int", 32);
        set("con", 35);
        set("unique", 1);

        set("no_get", "÷����������̫���ˡ�\n");
        set("max_qi",33500);
        set("qi",33500);
        set("max_jing",3000);
        set("neili", 24500);
        set("max_neili", 24500);
        set("jiali", 100);
        set("shen",-50000);

        set("combat_exp", 9400000);

        set_skill("claw", 450);
        set_skill("force", 450);
        set_skill("parry", 450);
        set_skill("dodge", 450);
        set_skill("leg", 450);
        set_skill("jiuyin-baiguzhua", 450);
        set_skill("bihai-chaosheng", 450);
        set_skill("suibo-zhuliu", 450);
        set_skill("xuanfeng-tui", 450);

        map_skill("force", "bihai-chaosheng");
        map_skill("parry", "jiuyin-baiguzhua");
        map_skill("dodge", "suibo-zhuliu");
        map_skill("claw", "jiuyin-baiguzhua");
        map_skill("leg", "xuanfeng-tui");
        prepare_skill("claw", "jiuyin-baiguzhua");

        create_family("�һ���", 2, "�������");
        set("inquiry", ([
		"�����׹�צ": (: jybgz :),
		"��ʬ":     "�����ϵ��˶���ô���ҵģ����²��£�����������",
		"��а":     "������ʦ���Ĵºš�",
		"����":     "�������ʦ�����ĸ���֮һ���Ǹ��϶��ס�ڰ���ɽ��",
		"�ϵ�":     "����ү�ѳ��ҵ�����ȥ�ˣ�������һ�ơ�",
		"��ؤ":     "��ؤͳ����ԭ��ؤ�������Ϊǿ��",
		"���߹�":   "���߹��书��ǿ�����ҽ̻������С������ʮ���ƣ��ɺޣ�",
		"����":     "������ʦ���Ķ�Ů�����ǵ������ԡ�",
		"����":     "�ߣ��������С�Ӱ�������ʦ�磬�Ҿ�����Ź�����",
		"�":     "�������ҵ�ͽ�ܣ��������ô��",
		"÷����":   "��������ô�����ǰ׳հ���",
		"������":   "�����ҵ�ʦ�磬Ҳ���ҵķ������ϧ��������С�������ˡ�",
		"��ҩʦ":   "������ʦ����",
		
	]) );
        setup();
}


string jybgz()
{
	object me = this_player();
	object ob = this_object();
	object kulou;
	int exp, time, night;
	mixed *local;
	night = 0;
	local = localtime(time() * 60);
	if (local[2] < 5 || local[2] >= 19) night = 1;	
	
	if ( me->query("shen") > 0) return "�㲻���ĺ����������ѧ������׹�צ�����С�\n";
	
	if( me->is_busy() || me->is_fighting() ) return "����æ���ء�\n";

	if( ob->is_busy() || ob->is_fighting() ) return ob->name()+"��æ���ء�\n";	
  
    if (!night) return "��ϰ�����׹�צ����ҹ���˾�ʱ�֣���������ν�������׹�צ�����С�\n";
    
	if( me->query("quest/jiuyin2/jybgz/pass") )
		return RANK_D->query_respect(me) + "�����Ѿ�ѧ������׹�צ���У��ֺιʿ�����Ц�أ�";

    if( me->query_skill("jiuyin-baiguzhua", 1) < 350 )
		return RANK_D->query_respect(me) + "����ľ����׹�צ���費�������޷������ҵľ�Ҫ���ڣ�";
 
	time = time() - me->query("quest/jiuyin2/jybgz/time");
	if( me->query("quest/jiuyin2/jybgz/time") && time < 86400)
		return "�ţ��㲻�Ǹ�����̹����𣿻�����Ŭ����ʱ��ɣ�";
	
	if( !kulou = present("kulou tou", me) ) {
		
		message_vision(CYN"$N��$n˵������ǰ��ָ����"+RANK_D->query_self(me)+"�����׹�צ�����У���\n"NOR, me, ob);
		message_vision(CYN"$n˵����" + RANK_D->query_respect(me) + "���Ȱ�����������ͷ�ɣ���\n"NOR, me, ob);
		me->start_busy(1);
		return "����ȥ�á�";
	} else {
		
		kulou->move(ob);
		me->start_busy(1);
		message_vision(CYN"$N����$n ������ͷ����÷����˵��������ǰ��ָ��"+RANK_D->query_self(me)+"�����׹�צ���壡��\n"NOR, me, ob);
	
	message_vision(HIW"ֻ��$n����$N�������ߣ��ǽ��з���΢΢���������Ų��𽥼ӿ죬�ǽڵ�����ҲԽ��Խ�죬Խ��Խ�ܣ����缸���ɹ�ͬʱ����һ��!"NOR, me, ob);
	COMBAT_D->do_attack(ob, me, 0, 1);
	message_vision(HIW"ֻ��$n˫�Ʋ�ס�ĺ��������ÿһ�������ֱ۹ؽ��ж��ǿ������죬������������ת�������Ժ��ϵñ�ֱ���������ɲ���"NOR, me, ob);
	COMBAT_D->do_attack(ob, me, 0,1);
	message_vision(HIW"ͻȻ��$n����һ���������ĵ�һ������$N��ǰ,�ۼ�$N����㵹��$n��ת��$N���һ�ƴ���$N���ġ�\nֻ��$n���δ춯�����������������������ƣ�һ�ƿ���һ�ƣ�һ������һ�ƣ�$Nʼ�շ�����һ����\n"NOR, me, ob);
	COMBAT_D->do_attack(ob, me,0, 1);
	message_vision(HIW"�����ھ��Ʒ�������$n��ȻԾ�𣬷����գ�ͷ�½��ϣ��۵�һ����������ָ������$N���š�\n"NOR, me, ob);
	
	message_vision(HIY"\n$Nƴ���ػ����Ÿղŵ���������ʼ����˼����.........\n", me);
	message_vision(HIY"\n$Nƴ���ػ����Ÿղŵ���������ʼ����˼����.........\n", me);
	message_vision(HIY"\n$Nƴ���ػ����Ÿղŵ���������ʼ����˼����.........\n", me);
	
	if( random(me->query("kar")) > 28) {	// �����Դ
			message_vision(HIW"$NͻȻ��׽ס����˲���һĻ����������������׹�צ�����С�\n", me);
			tell_object(me, BYEL"��ϲ�㣬����" + NATURE_D->game_time() + "�����˾����׹�צ�����С�\n"NOR);
			me->set("quest/jiuyin2/jybgz/pass", 1);
			me->set("quest/jiuyin2/jybgz/time",time());
			return "��ϲ����ϲ��";
		} else {
			message_vision(HIC"$Nҡ��ҡͷ�������������Ǻ����ѵġ���˵�գ������̾�˿�����\n", me);
			me->set("quest/jiuyin2/jybgz/time",time());
			return "��̫û���ã����°ɡ�";
		}
		
	}
	
}




void die()
{
	object ob = this_object(),me,cor;

	if (!ob->query_temp("target")){
		call_out("do_die",1,ob);
		return;
	}
        
	me = query_temp("last_damage_from");

	if (me->query("id") != ob->query_temp("target")) {
		ob->revive(1);
		command("say �ã���Ȼ����" + me->name(1) + "���㣬�ߣ�");
		message_vision(HIY"÷��������Ʋ��ã�ת�����ˣ�\n"NOR, me);
		destruct(ob);
		return;
	}
	else {
		if (me->query_temp("thd/onquest") > 2
		&& me->query_temp("thd/onquest") < 4) {
			ob->revive(1);
			ob->reicarnate();
			message_vision(HIY"÷��������д�����������������ݺݵĵ���$N��\n"NOR, me);
			if (objectp(cor = present("corpse",environment(ob)))) {
				tell_room(environment(ob),"÷���罫�������ʬ������������ڱ��ϡ�\n");
				call_out("do_dest",1,cor);
			}
			command("stare");
			command("say �ߣ����������ƣ�");
			message_vision(HIY"÷���籧��������ʬ��һ���۾Ͳ����ˡ�\n\n\n"NOR, me);
			if (me->query("thd/quest1") < 1 && random(me->query_kar()/10) > 0) {
				message_vision(HIW"$N��;�����ֺͺڷ�˫ɲ������ã���������һЩ��\n"NOR,me);
				me->set("thd/quest1",1);
			}
			me->set_temp("thd/onquest",4);
		}
		else if (me->query_temp("thd/onquest") > 5
			&& me->query_temp("thd/onquest") < 7 ) {
			me->set_temp("thd/onquest",7); 
			message_vision(HIM"÷�������ϵ���һ����Ƥ�������ذ�ס�\n"NOR,me);
			message_vision(HIM"$N��ذ�׺�Ƥ������������\n"NOR,me);
			new(resolve_path(0, __DIR__"../obj/skin"))->move(me);
			new(resolve_path(0, __DIR__"../obj/bishou"))->move(me);
			call_out("do_die",1,ob);
			return;
		}
		call_out("do_dest",1,ob);
		return;
	}
}

void do_die(object ob)
{
        :: die();
}

void do_dest(object ob)
{
        destruct(ob);
}

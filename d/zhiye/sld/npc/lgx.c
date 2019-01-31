// ½����

inherit F_MASTER;
inherit NPC;
#define	SEAWAR_D	"/d/sld/seawar/seaward"
#include "ansi.h"

int ask_lingpai();
int ask_yaopu();
int ask_yaolu();
int ask_yaozhong();
int ask_makeyao();
int ask_shedu();
string ask_pendu();

string ask_seawar();

void create()
{
	set_name("½����", ({ "lu gaoxuan","lu" }));
	set("long", "����ʮ������ͣ���ʿ��磬����Ͱ����ף����������̵Ļ�����\n");
	set("gender", "����");
	set("title", "�����̻���");	
	set("age", 42);       

	set("str", 20);
	set("int", 22);
	set("con", 50);
	set("dex", 22);
	set("per", 22);
	
	set("no_ansuan",1);
	set("no_bark",1);
	set("no_quest",1);
	set("no_get",1);

	set("combat_exp", 95000000);
	//set("shen", -5000);
	set("attitude", "peaceful");
	set("max_qi",98500);
	set("max_jing",98500);
	set("neili",98000);
	set("max_neili",98000);
	set("jingli",98000);
	set("eff_jingli",98000);
	set("jiali",200);
	set("score", 2000);

	set_skill("force", 450);
	set_skill("dodge", 450);
	set_skill("parry",450);
	set_skill("strike",450);
	set_skill("throwing",450);
	set_skill("literate",450);
	set_skill("poison",450);
	set_skill("shenlong-yaoli",450);
	set_skill("huagu-mianzhang", 450);
	set_skill("youlong-shenfa",450);
	set_skill("dulong-dafa",450);
	set("startroom","/d/sld/lgxroom");
      
	map_skill("force", "dulong-dafa");
	map_skill("dodge", "youlong-shenfa");
	map_skill("strike", "huagu-mianzhang");
	map_skill("parry","huagu-mianzhang");
	prepare_skill("strike","huagu-mianzhang");
      
	create_family("������",2, "����");
	set("chat_chance", 2);
	set("chat_msg", ({
		CYN"½����˵�������ҩ���Ƶò��࣬����\n",NOR
		CYN"½����˵������������ǿ��׳��������ɲ�˰�æ��˭�����¡�\n"NOR,
		CYN"½����˵������ɲ�˵��ڴ�������������ս��ʤ���ɣ�\n"NOR,
		CYN"½����˵�����к�������ӣ���ս��ʤ��\n"NOR,
	}) );
	set("inquiry", ([
		"����" : (: ask_lingpai :),
		"ͨ������" : (: ask_lingpai :),
		"lingpai" : (: ask_lingpai :),
		"ling pai" : (: ask_lingpai :),
		"������" : (: ask_shedu :),

		"�������" :	(: ask_seawar() :),
		"job" :		(: ask_seawar() :),
		"����" :	(: ask_seawar() :),
		"���" :	"�������ں��峯ˮʦ����֮�У�������ս�ɣ��ô��ٲ�����ġ�",
		"�綾����" :	(: ask_pendu() :),
//		"ҩ��": (: ask_yaopu :), 
//		"��ҩ": (: ask_makeyao :),
//		"��ҩ": (: ask_makeyao :),
//		"ҩ¯": (: ask_yaolu :),
//		"ҩ��": (: ask_yaozhong :),
	]));

	setup();
	carry_object(__DIR__"obj/changsan")->wear();     
}


void init()
{
	add_action("do_steal","steal");
}

int do_steal(string arg)
{
	object ob=this_object();
	object me=this_player();
	object lpai;

	if(arg!="����" && arg!="ͨ������" && arg!="lingpai" && arg!="ling pai")
		return 0;

	if(!living(ob))
		return notify_fail("½������������û�����ƿ���͵��\n");

	lpai = present("ling pai", me);
	if(objectp(lpai) &&  lpai->query("sld")) {
		write("���Ѿ��������ƣ���͵��������\n");
		return 1;
	}
	tell_object(me,"�㲻����ɫ�ؿ���½������͵͵�ذ�����½��������ȥ...\n");
	if(me->query("kar") > random(20)) {
		tell_object(me,"��ɹ���͵���˿�ͨ������!\n");
		lpai= new(__DIR__"obj/lingpai");
		lpai->move(me);
	}
	else {
		tell_room(environment(me),CYN"½���������е���"+me->name()+"�㾹��͵���ƣ�������ˣ�\n"NOR);
		tell_room(environment(me),CYN"½����һ�Ű�"+me->name()+"���˳�ȥ��\n"NOR);
		if (me->query("qi") > me->query_skill("force",1))
		me->receive_damage("qi",me->query_skill("force", 1));
		else me->set("qi", 1);
		me->move("/d/sld/kongdi");
	}
	return 1;       
}

int prevent_learn(object me, string skill)
{
	return 0;
}

void unconcious()
{
	object ob=this_object();
	object me;
	if (objectp(me=ob->query_temp("last_damage_from")))
	{
		log_file("attack_nokill_npc",sprintf("%s %s͵Ϯ½������\n", me->query("id"),me->query("name")), me);	
	}
	
	return;
}

int recognize_apprentice(object ob)
{
	mapping myfam;

	myfam = (mapping)ob->query("family");
	if(!(myfam["family_name"] != "������")
	 && ob->query("shen",1) < -10000
	 && ob->query_skill("dulong-dafa",1) >= 100 
	 && ob->query_skill("huagu-mianzhang",1)>=100 ) {
		if(random(10) > 7)
		return 1;
	}
	return 0;
}

int ask_lingpai()
{
	object me,ob,zs;
	mapping myfam;
	object* inv;
	int i;

	me=this_player();
	ob=this_object();
	myfam = (mapping)me->query("family");
	if(!myfam || myfam["family_name"] != "������") {
		return 0;
	}
	inv = all_inventory(me);
	for(i=0; i<sizeof(inv); i++)       
	if(inv[i]->query("id")=="ling pai")
		break;
	if(i>=sizeof(inv)) {
		zs= new(__DIR__"obj/lingpai");
		if (!zs)  return notify_fail("�쳣����\n");
		tell_object(me,"��Ȼ��Ҫ�������Ҿ͸�������ưɡ�\n");
		tell_room(environment(me), "½������" + me->name() + "һ�����ơ�\n");
		zs->move(me);      
	}
	else {
		tell_object(me,"�㲻���Ѿ���������ô��\n");
	}
	return 1;
}
//ask ҩ��
int ask_yaopu()
{
	object me=this_player();
	
	if(!me->query_temp("makeyao",1)) {
		return 0;
	}
	tell_object(me,"½��������˵�����Ҹ�����һ��ھ���������ԣ�˳ʱ���У�������Ϣ�������ѭ��Ǭ��Ϊ�ף��޶�Ϊβ��\n");
	return 1;
}
//ask about ��ҩ
int ask_makeyao()
{
	object me=this_player();
	mapping myfam;

	myfam = (mapping)me->query("family");
   	if(!myfam || myfam["family_name"] != "������") {
		return notify_fail("��������̣�����������!\n");
   	}
	if(me->query_skill("shenlong-yaoli",1)<101 || me->query_skill("poison",1)<101)
		return notify_fail("�������ҩ��򶾼ƶ�����101��!\n");
	tell_object(me,"½��������˵��������������������ҩ����ҩ��֮�У�����ɲĺ�����ҩ¯֮�У��Ա����ܷ���֮���ɵ�ҩ��\n");
	me->set_temp("makeyao",1);
	return 1;
}
//ҩ¯
int ask_yaolu()
{
	object me=this_player();
	object yl;

	if(!me->query_temp("makeyao",1))
   	{
       		return notify_fail("������������Ī�����!\n");
   	}
	if(objectp(yl=me->query("myyaolu")))
	{
		if(random(10)>2)
			return notify_fail("�����Ѿ�������ҩ¯��ô��\n");
		else
			destruct(yl);
	}
	yl=new("/d/sld/npc/obj/yaolu");
	if(!yl)
		return notify_fail("����û��ҩ¯����Ȼ�����Ҫ�ɡ�\n");
	else if(!yl->move(me))
	{
		destruct(yl);
		return notify_fail("���Ȱ�����û�õĶ����������Ȼ������Ҫҩ¯�ɡ�\n");
	}
	else
	{
		yl->set("owner",me);
		tell_object(me,"½����������һֻҩ¯����������ֻҩ¯��ҩȥ�ɡ�\n");
		me->set("myyaolu",yl);
	}
	return 1;
}

int ask_yaozhong()
{
	object me=this_player();
	
	if(!me->query_temp("makeyao",1))
   	{
       		return 0;
   	}
	else if(me->query_temp("yaozhong",1))
	{
		return notify_fail("�Ҳ����Ѿ�����˵����ô������ô�����ˣ�\n");
	}
	tell_object(me,"½��������˵�������ϴβ�֪����ҩ����������ȥ�ˣ������ҵ����ٸ��㡣\n");
	me->set_temp("yaozhong",1);
	return 1;
}

void kill_ob(object ob)
{
	object me = this_object();
	command("say �Ϸ����ڳﻮ�Կ������û���������档");
	me->remove_enemy(ob);
	ob->remove_killer(me);
	ob->add_busy(999);
	command("chat "+ob->query("name")+"("+ob->query("id")+")"+"Ҫɱ���ң����������е���Ҫ���ұ��𰡣�\n");
	ob->set_temp("attack/lgx",1);
	//��ǣ�������id�ɵ�
	log_file("quest/badmanlist", sprintf("%8s(%8s) ����ɱ��½��������¼�ڰ���\n",ob->name(1),ob->query("id")));
		
	if (ob->query_condition("killer") < 100) ob->apply_condition("killer", 200);
	return;
}

int accept_fight(object ob)
{
	
	ob->add_busy(999);
	ob->set_temp("attack/lgx",1);
	command("chat ���ӽ�����"+ob->query("name")+"("+ob->query("id")+")"+"����ս�����������ˣ����������е���Ҫ���ұ��𰡣�\n");

	command("say �Ϸ����ڳﻮ�Կ������û���������档");
	log_file("quest/badmanlist", sprintf("%8s(%8s) ����fight½��������¼�ڰ���\n",ob->name(1),ob->query("id")));

	return 1;
}

string ask_seawar()
{
	object * team;
	object me;
	int i;
	
	me = this_player();
	team = me->query_team();
	
	if(wizardp(me) && me->query("env/test"))
		return SEAWAR_D->play(me,me,2);
	
	if( sizeof(team) != 2 )
		return "������ս����Ķ������Ҫ�������ˡ�";
	for (i=0;i<sizeof(team);i++) {
		if ( !team[i] || !userp(team[i]) || !present(team[i],environment(me)) )
			return "��Ҫ��˭һ���ս��";
		if( team[i]->query_condition("job_busy") 
			|| team[i]->query("job_name")=="��������ս" || team[i]->query_condition("killer") )
			return "���ǵĶ���̫æµ�ˣ���Ϣһ����ٲ�ս�ɡ�";
		if( team[i]->query("combat_exp")<100000 )
			return "���ǵĶ���ľ���̫���ˣ�������ȥ����һ�¶�������ս�ɡ�";
		if( team[i]->query("job_name")=="��������ս" )
			return "���ǵĶ���ľ���̫���ˣ�������ȥ����һ�¶�������ս�ɡ�";

		if( team[i]->query("shen")>-30000 )
			return "�����ƺ������ҵ����ˣ��ҿɲ����������ǲ�ս��";
	}

	return SEAWAR_D->play(team[0],team[1],2);
}

int ask_shedu()
{
	object me,ob;
	me=this_player();
	if (!me->query_temp("quest/kl/klz/hongsha/asklu"))
	{
		command("say �������Ե�޹ʣ���Ҫ���룡\n");
		return 1;
	}
	command("consider ");
	command("say ��Ȼ�Ƿ�������ǰ�����������ң����ҾͰ���һ��!\n");
	command("say ���Ǹ����һ�����߶��ۣ���Ҫ�ú��ˣ�ǧ������ˡ�\n");
	command("say ����綾���мǲ������׺���ͿĨ(tumo)�����ж�������Ϊ������ĳ������Ĺ���\n");
	ob=new("d/sld/npc/obj/shefen.c");
	ob->move(me);
	me->delete_temp("quest/kl/klz/hongsha/asklu");
	return 1;
}

//������
void die()
{
	object me,ob,room;
	//ob=this_object();
	//room=load_object("d/sld/lgxroom");
	
	if (!query_temp("living")) {
		ob = new("/d/sld/npc/lgx");
		ob->move("/d/sld/lgxroom");
	}
	
	::die();
}

//�綾����
string ask_pendu()
{
	object me;
	int i,j;
	me=this_player();
	if (!me->query("quest/sld/dldf/pendu/start"))
	{
		return "����δ�˽����ҩ����������֮������Ҳ�״\n";
	}
	if (me->query_skill("zhiyao",1)<200)
	{
		return "��ҩ����Ҫ�ﵽ200��ɽ׶η�����ϰ��\n";
	}
	if (me->query_skill("force",1)<450)
	{
		return "�����ڹ��ﵽ450��ɽ׶η�����ϰ��\n";
	}
	if (me->query("family/family_name")!="������")
	{
		return "�㲢�����������ӣ�\n";
	}
	if (time()-me->query("quest/sld/dldf/pendu/time")<86400)
	{
		return "������̫Ƶ���ˣ�\n";
	}
	if (me->query("quest/sld/dldf/pendu/pass"))
	{
		return "���Ѿ��⿪��������ˣ�\n";
	}
	command("consider ");
	message_vision(HIY"½������$N˵������ܲ�����Ȼ������ҩ����������ô�����򣬿����ǿ���֮�ģ���\n"NOR,me);

	command("say ��������������ɫ֮һ���Ƕ��ڸ���ҩ����о���\n");
	command("say ��������һ�������Ҳŷ��֣�������������������ڣ�Ȼ����϶����󷨡�\n");
	command("say �����ڶ�ս�����н�����Ķ�ҩ�����������Է�����ʤ����\n");
	command("say �Է�һ���ж����������ض�����������ҩ��\n");
	command("say ��������Ȥ�Ҿͽ����ž����������㣡\n");
	
	me->set_temp("quest/sld/dldf/pendu/asklu",1);
	
	command("say ���������������������Ҫ�۳�������ɹ���ֵÿ��100�㣬���������û�ʸ�����ҡ�\n\n\n\n");
	
    command("say �ðɣ���Ȼ�����Ŭ�����Ҿ͸��������о��ϡ�\n");
    command("whisper "+me->query("id"));
	  
	if (me->is_busy())
	{
	  return "������æµ��!\n";
	}
	me->start_busy(10);
	if (me->query("party/gongji")<100)
	{
		return "������ɹ�������\n";
	}
	
	me->add("party/gongji",-100);
	i = 20;
		if(me->query("m-card-vip")) i =  18;
		if(me->query("y-card-vip")) i =  15;
		if(me->query("buyvip"))     i =  10;
		i=random(i);
		j=random(me->query("kar"));
		command("say ��������ô��\n");
		command("pat "+me->query("id"));
		if( i<4
			&& me->query("kar")<31
			&& random(me->query_con(1))>35
			&& j > 27 ) 
		{
			tell_object(me,HIC"\n�����˵�½����������ָ�㣬�����������Լ���ҩ�����е������ĵã����±˴�ӡ�գ������ĵá�\n"NOR);
			tell_object(me,HIR"\n�㰴��½������ָ�㣬������Ķ�ҩ�Զ�������ʹ����Ȼ������һʹ��˲�����������綾���������������š�\n"NOR);
			tell_object(me,HIB"\n���ſ����һ����ڵ����壬״����ì��Լ�����࣬��˸������\n"NOR);
			tell_object(me,HIY"\n������ǧ����࣬�������ɶ������綾������\n"NOR);

			me->set("quest/sld/dldf/pendu/pass",1);
			log_file("quest/sldpendu", sprintf("%8s(%8s) ʧ��%d�κ�ѧ���������綾����,�����ڻ��ͨ�������iȡֵ��%d|�����Դjȡֵ��%d|��ǰ��Դȡֵ��%d|������ǣ�%d��\n",
				me->name(1),me->query("id"), me->query("quest/sld/dldf/pendu/fail"),i,j,me->query("kar"),me->query_con(1)) );
			command("haha"+me->query("id"));		
			me->delete_temp("quest");
			me->start_busy(2);
			return "��ϲ�����綾�����ɹ�!\n";
			
		}	
	   else
		{
			log_file("quest/sldpendu", sprintf("%8s(%8s) �����綾����ʧ��%d�Σ��������iȡֵ��%d|�����Դjȡֵ��%d|��ǰ��Դȡֵ��%d|���飺%d��\n",
				me->name(1),me->query("id"), me->query("quest/sld/dldf/pendu/fail"),i,j,me->query("kar"),me->query_con(1)) );
			
			tell_object(me,HIY"������½������ָ�㣬���Ƕ��綾�����İ���ȫȻ����Ҫ�졣\n\n"NOR);
			command("sigh "+me->query("id"));
			command("disapp "+me->query("id"));
			me->add("quest/sld/dldf/pendu/fail",1);
			me->set("quest/sld/dldf/pendu/time",time());
			me->start_busy(2+random(3));
			me->delete_temp("quest");
			me->start_busy(2);
			return "�ǳ��ź������綾����ʧ��"+me->query("quest/sld/dldf/pendu/fail")+"�Ρ�\n";
		}

	


}
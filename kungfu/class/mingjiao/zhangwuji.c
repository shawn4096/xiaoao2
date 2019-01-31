// NPC zhangwuji.c ���޼�
// Modify By River@SJ 99.6

#include <ansi.h>
#include "zhangwuji.h";
inherit NPC;
inherit F_MASTER;
string ask_book();
string ask_qishang();
string ask_shu();
string ask_me();
int ask_hdg();
string ask_ling();
string ask_getling();
string ask_fel();
string ask_jiuyang();
string ask_xinfa();
string ask_was();
int ask_shlf();
int pfm_zhen();
int pfm_chan();
int pfm_yi();
int pfm_qishang();
int pfm_tougu();
int pfm_tisha();
int pfm_duanhun();
int ask_hu_quest();
int ask_hu();
int ask_ronghe();
int ask_qsqzj();

void create()
{
	object weapon;
	set_name("���޼�",({"zhang wuji","zhang","wuji"}));
	set("title",HIY"���̵���ʮ�Ĵ�����"NOR);
	set("long", "���������̵ĵ���ʮ�Ĵ����������ϴ���Ӣ�ʲ�����Ц�ݡ�\n");
	set("age", 25);
	set("per", 32);
	set("attitude", "friendly");
	set("shen", 40000);
	set("str", 35);
	set("int", 30);
	set("con", 50);
	set("dex", 30);

	set("max_qi", 50000);
	set("max_jing", 7500);
	set("neili", 50000);
	set("eff_jingli", 7500);
	set("max_neili", 50000);
	set("jiali", 150);
	set("combat_exp", 15000000);
	set("unique", 1);
	set("no_bark",1);
	set("mj/qkdny/ronghe",1);
	set("mj/jiuyang/pass",3);
	set("mj/quest/yzs",1);
	//set("",1);


	set_skill("sword", 550);
	set_skill("dodge", 550);
	set_skill("force", 550);
	set_skill("dagger", 550);
	set_skill("strike", 550);
	set_skill("hanbing-mianzhang", 550);
	set_skill("piaoyi-shenfa", 550);
	set_skill("tiyunzong", 550);
	set_skill("shenghuo-lingfa", 550);
	set_skill("jiuyang-shengong", 550);
	set_skill("lieyan-dao", 550);
	set_skill("blade", 550);
	set_skill("liehuo-jian", 550);
	set_skill("taiji-jian", 550);
	set_skill("taiji-quan", 550);
	set_skill("parry", 550);
	set_skill("cuff", 550);
	set_skill("qiankun-danuoyi", 550);
	set_skill("qishang-quan", 550);
	set_skill("literate", 550);
	set_skill("medicine", 550);
	set_skill("xiaoyao-jian", 550);
    //set_skill("medicine", 550);
	set_skill("shenghuo-shengong", 550);
	set_skill("shenghuo-fumozhen", 550);
	set_skill("yingzhua-shou", 550);
	set_skill("hand", 550);

	map_skill("force", "jiuyang-shengong");
	map_skill("cuff","qishang-quan");
	map_skill("dagger","shenghuo-lingfa");
	map_skill("sword","taiji-jian");
	map_skill("dodge", "tiyunzong");
	map_skill("blade", "lieyan-dao");
	map_skill("strike", "hanbing-mianzhang");
	map_skill("parry", "qiankun-danuoyi");
	prepare_skill("cuff","qishang-quan");

	set("chat_chance_combat", 90);
	set("chat_msg_combat", ({
		(: pfm_hua :),
		//	(: pfm_hua :),
		(: pfm_tisha :),
		(: pfm_qishang :),
		(: pfm_tougu :),
		(: pfm_yi :),
		//(: pfm_zhen :),
		(: pfm_duanhun :),
	}));

	create_family("����",34,"����");

	set("inquiry", ([
		"��˹����" : "����������Դ�ڲ�˹���̣����м�������ʷ�ˣ�����С�����Ҷ�ȥ��\n"+
			"�β�˹��������֪���ɺã������г�˼��������......",
		//"ʥ����" : "ʥ�����������̵�ʥ�����ʧ����ꡣ",
		"лѷ" : "�常���ټ������ǲ��������˽��ġ�",
		"����ͨ"  : (: ask_hu_quest :),
		"����ţ"  : (: ask_hu :),
		"������"  : (: ask_hdg :),
		"�ؼ�"  : (: ask_book :),
		"����ȭ��"  : (: ask_qishang :),
		"����ȭ��" : (: ask_shu :),
		"ʥ����" : (: ask_me :),
		"����" : (: ask_ling :),
		"������" : (: ask_getling :),
		"Ǭ����Ų����" : (: ask_ronghe :),
		//"������" : (: ask_jiuyang :),
	    "ʥ���ķ�" : (: ask_xinfa :),
		"ʥ�������" : (: ask_shlf :),
		"����ȭ�ܾ�" : (: ask_qsqzj :),

		"���Ʒ�����" : (: ask_fel :),
		"����" : (: ask_was :),
	]));

	set_temp("apply/damage", 90);
	set_temp("apply/dodge", 90);
	set_temp("apply/attack", 90);
	set_temp("apply/armor", 90);
	setup();

	if (clonep()){
		if( sizeof(filter_array(children(BINGQI_D("shangshan_ling")), (: clonep :))) > 0 )
			weapon = new(BINGQI_D("tieling"));
		else if( sizeof(filter_array(children(BINGQI_D("fae_ling")), (: clonep :))) > 0 )
			weapon = new(BINGQI_D("tieling"));
		else weapon = unew(BINGQI_D("sf_ling"));
		if (!weapon) weapon = new(BINGQI_D("tieling"));
		carry_object(BINGQI_D("sword"));
		weapon->move(this_object());
		weapon->wield();
		carry_object("/d/mingjiao/obj/white-cloth")->wear();
	}
}

void init()
{
	::init();
	add_action("do_lingwu","taojiao");
	add_action("do_kill", "kill");
	add_action("do_kill", "teamkill");
	add_action("do_kill", "tk");
	add_action("do_kill", "hit");
}

void reset()
{
	object ob;

	if (clonep()) {
		if (!(ob = unew(BINGQI_D("shangshan_ling"))))
			return;
		destruct(ob);
		if (!(ob = unew(BINGQI_D("fae_ling"))))
			return;
		destruct(ob);
		if (ob = unew(BINGQI_D("sf_ling"))) {
			ob->move(this_object());
			command("wield shangshanfae ling");
		}
	}
}

void attempt_apprentice(object ob)
{
	mapping fam = ob->query("family");
	if (!fam || fam["family_name"] != "����"){
		command("say "+RANK_D->query_respect(ob)+"�뱾��������������֪�˻��Ӻ�̸��");
		return;
	}
	if((int)ob->query_skill("shenghuo-shengong", 1) < 350) {
		command("say ������֮ʥ�����˼��õ��ڼ��ķ�������350��ʥ����Ҫ����������");
		command("say " + RANK_D->query_respect(ob)+"�Ƿ�Ӧ�������ڹ��϶��µ㹦��");
		return;
	}
	if((int)ob->query_skill("medicine", 1) < 80) {
		command("say ����ѧ���ӣ��������������ҽ�顣");
		command("say "+RANK_D->query_respect(ob)+"�Ƿ�Ӧ�����ڱ��������϶��µ㹦��");
		return;
	}
	if((int)ob->query_skill("literate", 1) < 200) {
		command("say ����ѧ���ӣ���Ҫ��ѧ�ñ����ȱ���ʫ��,����200�������ҡ�");
		command("say "+RANK_D->query_respect(ob)+"�Ƿ�Ӧ�����ڶ���д���϶��µ㹦��");
		return;
	}
	if((int)ob->query("shen") < 1000000) {
		command("say ѧ��֮�ˣ�����Ϊ�ȣ�����ĸߵ͵�������Σ�δ���䣬Ҫ��ѧ���ˡ�");
		command("say ���ڵ��з��治��1M����"+RANK_D->query_respect(ob)+"�Ƿ����ò�����");
		return;
	}
	if(ob->query_int() < 32) {
		command("say �ҵ��书��Ҫ���ߵ����Բ���ѧ�ᡣ");
		command("say Ҫ�ܴﵽ¯����֮��������ʲô�ĵ����޹ؽ�Ҫ������ȴ�ǰ��Ҳ�����á�");
		command("say "+RANK_D->query_respect(ob)+"�����Ի�����Ǳ�����ڣ�������ذɡ�");
		return;
	}
	command("say �ţ����㻹�Ǹ�ѧ����ϣ��Ҿ�������ɣ�");
	command("say ��л������ӣ����������ֵ�һ���ģ�Ϊ�������壬�������̷�����ɡ�");
	command("recruit " + ob->query("id"));
	ob->set("title",HIR"���̽����״�����"NOR);
	/*if( ob->query_skill("dagger", 1) < ob->query_skill("balde", 1) ){
		ob->set_skill("dagger", ob->query_skill("balde", 1));
		tell_object(ob, "���ܵ�����ָ�㣬ذ���Ѿ��ﵽ�˵����ľ��磡\n");
	}*/
}

int do_kill(string arg)
{
	object ob,ob2;
	object me = this_player();
	ob2 = this_object();

	if (!arg) return 0;
	ob = present(arg, environment(me));
	if (ob == this_object() || ob == me) return 0;
	if (!ob || !ob->is_character()) return 0;


	if (userp(ob) && ob->query("family/family_name") == "����") {
		if (me->query("family/family_name") == "����") {
			message_vision(ob2->name()+"��$N�ȵ�����Ϊ���̵��ӣ���Ȼɱ�Լ���ͬ�ţ��������㣡\n", me);
		}
		else {
			message_vision(ob2->name()+"��$N�ȵ����󵨿�ͽ����Ȼ���ѱ������������\n", me);
			kill_ob(me);
		}
		me->set("vendetta/����", 1);
		return 1;
	}
	return 0;
}

int ask_ronghe() 
{
	int i,j;
	object me = this_player();
	if(this_object()->is_fighting()) return 0;
	message_vision(HIC"$N��$n����й�Ǭ����Ų�ƾ������������\n"NOR, me, this_object());
	if(me->query("family/family_name")!="����"||me->query("family/master_id")!="zhang wuji")
	{
		command("?");
		command("say �㲻���ҵ��״����ӣ��ѵ�������͵ѧ��");
		command("kick "+me->query("id"));
		return 1;
	}
	if(me->query("int") < 40)
	{
		command("?");
		command("say Ǭ����Ų����Ҫ���ߵ��������ԣ�����������Բ���40, Ŭ������ȥ�ɣ�"NOR);
		command("kick "+me->query("id"));
		return 1;
	}
	if(me->query("mjqkdny/pass"))
	{
		command("?");
		command("say ���Ѿ����������Ǭ����Ų�ƾ����İ��أ��ѵ���������ǲ�����ӣ�"NOR);
		command("kick "+me->query("id"));
		return 1;
	}
	command("look "+me->query("id"));	
	//��ͨ�������
	
	if(me->query("mjqkdny/fail")>=3 && me->query("registered")<3)
	{
		command("shrug "+me->query("id"));
		command("say �Ѿ���δ��ڣ�����ô����û������,�湻���ģ�");
		command("puke "+me->query("id"));
		return 1;
	}
	//�书ѧϰ֮����Ҫ���һ�죬������Ҫ���50K
	if( time()-me->query("mjqkdny/time")<86400)
	{
		command("shake "+me->query("id"));
		command("say �����Ƚ̵�������ɣ�����ɡ�");
		return 1;
	}
	if(me->query_skill("qiankun-danuoyi",1)<450)
	{
		command("look "+me->query("id"));
		command("say ���㵱ǰ��Ǭ����Ų�Ʋ���450�������»����������򣬻���ץ��ȥ����ȥ�ɡ�");
		return 1;
	}
    
	me->set("mjqkdny/time",time());
	me->set("mjqkdny/combat_exp",me->query("combat_exp")); 
	i= random(20);
	command("sigh "+me->query("id"));
	command("say Ǭ����Ų�ƾ������������̵�����书����Ȼ����������Ҿ�˵����������������û����������ˡ�");
	command("whisper "+me->query("id"));
	command("smile "+me->query("id"));
	
	j = 20;
    if(me->query("m-card-vip")) j =  18;
    if(me->query("y-card-vip")) j =  15;
    if(me->query("buyvip"))     j =  10;
	i=random(j);
	if(i<3 
		&&random(me->query("int"))>40
		&& random(me->query("kar"))>=27)
	{
		tell_object(me,HIC"\n�㰴�����޼ɵ�ָ�㣬��Ǭ����Ų�Ƶ��ռ������ƺ���Щ�ĵá�\n"NOR);
        tell_object(me,RED"\nһ�������ľ����ӵ��￪ʼ�����������Ͷ���ѭ��һȦ������������¥�������أ������ţ������\n"+
			"�������ԽתԽ�죬����������뺣֮�ơ���о���ʱȫ������Ȼ��ͨ��ȫ����������\n"+
			"��ǰ�ܶ಻���׵Ĵ�ʱ���������ף��ҿ���ǰ��û�����ɵ�ʮ�ž�ȥǿ��������������߻���ħ���ɡ�\n"NOR);
		tell_object(me,HIY"\n�㽫���޼ɽ�������ݺ���ǰ�Լ���ѧ�໥ӡ֤���漴�����̲�ס������Ц��\n"NOR);
		tell_object(me,HIC"\n��ϲ������ǧ����࣬���ڽ⿪Ǭ����Ų���ռ����ء�\n"NOR);
        tell_object(me,HIR"\n���Ѿ���Ǭ����Ų�Ƶ��߲��񹦳����ڻ��ͨ��\n"NOR);
       
		
		//me->improve_skill("wuxiang-zhi", 10+random(me->query_int()));
		command("look "+me->query("id"));
		command("pat "+me->query("id"));
		command("haha "+me->query("id"));
		//me->set(QUESTDIR4+"sword",1);
		me->set("mjqkdny/pass",1);
		me->set("title",HIR"Ǭ��"HIC"��"HIG"Ų��"HIR"����"NOR);		
		me->set("mytitle/quest/qkdnytitle",HIR"Ǭ��"HIC"��"HIG"Ų��"HIR"����"NOR);
		me->add("qkdny",1);
		log_file("quest/mjqkdny", sprintf("%8s(%8s) ʧ��%d�κ󣬳�������Ǭ����Ų�Ƶľ�����iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"), me->query("mjqkdny/fail"),i,me->query("combat_exp")) );
	}
	else
	{
		me->add("mjqkdny/fail",1);
		command("poor ");
		tell_object(me,HIY"���������޼ɵ�ָ�㣬��Ȼ��˵�������书�İ��أ����Ƕ�Ǭ����Ų�Ƶ��ռ�����ȫȻ����Ҫ�졣\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		//me->set("mj/qkdny/ronghe/time",time());
       // me->set("mj/qkdny/ronghe/time",time());
		log_file("quest/mjqkdny", sprintf("%8s(%8s) Ǭ����Ų���ռ����ؽ���ʧ��%d�Ρ�iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"),me->query("mjqkdny/fail"),i,me->query("combat_exp")) );
	}
	return 1;
}


int ask_shlf() 
{
	int i;
	object me = this_player();
	if(this_object()->is_fighting()) return 0;
	message_vision(HIC"$N��$n����й�ʥ����������������\n"NOR, me, this_object());
	if(me->query("family/family_name")!="����"||me->query("family/master_name")!="���޼�")
	{
		command("?");
		command("say �㲻���ҵ��״����ӣ��ѵ�������͵ѧ��");
		command("kick "+me->query("id"));
		return 1;
	}

	if(me->query("quest/mj/shlf/jueji/pass"))
	{
		command("?");
		command("say ���Ѿ����������ʥ��������İ��أ��ѵ���������ǲ��������"NOR);
		command("kick "+me->query("id"));
		return 1;
	}
	command("look "+me->query("id"));	
	//��ͨ�������
	//�������40
	if (me->is_busy())
	{
		command("say ����æ����!\n");
		return 1;
	}
	if(me->query("str")<40)
	{
		command("shrug "+me->query("id"));
		command("say ����������̫���ˣ�����40��");
		command("addoil "+me->query("id"));
		return 1;
	}
	if(me->query("quest/mj/shlf/jueji/fail")>=3 && me->query("registered")<3)
	{
		command("shrug "+me->query("id"));
		command("say �Ѿ���δ��ڣ�����ô����û������,�湻���ģ�");
		command("puke "+me->query("id"));
		return 1;
	}
	//�书ѧϰ֮����Ҫ���һ�죬������Ҫ���50K
	if( time()-me->query("quest/mj/shlf/jueji/time")<86400)
	{
		command("shake "+me->query("id"));
		command("say �����Ƚ̵�������ɣ�����ɡ�");
		return 1;
	}
	if(me->query_skill("shenghuo-lingfa",1)<450)
	{
		command("look "+me->query("id"));
		command("say ���㵱ǰ������ȭ��������450�������»����������򣬻���ץ��ȥ����ȥ�ɡ�");
		return 1;
	}
	if(!me->query("quest/mj/shlf/givezhang"))
	{
		command("look "+me->query("id"));
		command("say �㲻ȥ�����ҵ�ʥ������¶������ž��������������򣬻���ץ��ȥ����������ɡ�");
		return 1;
	}
	if (!me->query_temp("lianji/killcheng"))
	{
		command("say ���������ҽ������У���ȥ��������ɱ�ˣ�����ͷ�������Ҿʹ�������������");
		return 1;
	}
    if (!me->query_temp("lianji/songfa"))
	{
		command("say ������ȥ����£�������Ҫһ�����常лѷ�Ľ𷢣��������ỵ�Һ��ܹ���Ĵ��¡�");
		command("smile zhang wuji");
		command("sigh zhang wuji");
		me->set_temp("lianji/askzhang",1);
		return 1;
	}
	me->set("quest/mj/shlf/jueji/time",time());
	me->set("quest/mj/shlf/jueji/combat_exp",me->query("combat_exp")); 
	i= random(20);
	command("sigh "+me->query("id"));
	command("say ʥ����������������̵�����书֮һ����Ȼ����������Ҿ�˵����������������û����������ˡ�");
	command("whisper "+me->query("id")+"������ң��Ҽ�Ϊ����Ϊ��...��");
	command("smile "+me->query("id"));
	me->start_busy(99);
	remove_call_out("thinking_shlf");
	call_out("thinking_shlf",1,me);	
	return 1;
}

int thinking_shlf(object me)
{
	int i,j,total;
	if(!me) return 0;
	
	if(me->query_temp("lianji/ask")<(3+random(3)))
    { 
	  me->add_temp("lianji/ask",1);
      if(random(2)) tell_object(me,HIG"\n����������Ÿղ����޼���������ʥ���������һ��һʽ...\n"NOR);
             else tell_object(me,HIY"\nͻȻ�䣬���ƺ�ץ����ʲô...\n"NOR);
	  tell_room(environment(me),HIC""+me->query("name")+"�ƺ���˼����ʲô��üͷ���塣\n"NOR, ({}));
	  remove_call_out("thinking_shlf");
	  call_out("thinking_shlf",3+random(3), me);
	}
	else
	{  
	  me->delete_temp("lianji/ask");
      total = me->query("str") + me->query("con")+ me->query("dex")+ me->query("int");
      j = 20;
      if(me->query("m-card-vip")) j =  18;
      if(me->query("y-card-vip")) j =  15;
      if(me->query("buyvip"))     j =  10;
	  i= random(j);
	  if(i<3 
		  &&random(me->query("str")>40)
		  && random(me->query("kar"))>=26)
	  {
		tell_object(me,HIC"\n�㰴�����޼ɵ�ָ�㣬��ʥ����������ռ������ƺ���Щ�ĵá�\n"NOR);
        tell_object(me,RED"\n���Ȼ��ζ����ʥ��������ľ��������������������ߵ����벨˹��ʹ��ս�ľ�����\n"NOR);
		tell_object(me,HIY"\n�㽫���޼ɽ�������ݺ���ǰ�Լ���ѧ�໥ӡ֤���漴�����̲�ס������Ц��\n"NOR);
		tell_object(me,HIC"\n��ϲ������ǧ����࣬���ڽ⿪ʥ��������ռ����ء�\n"NOR);
        tell_object(me,HIR"\n���Ѿ���ʥ����������ռ����س����ڻ��ͨ��\n"NOR);
    
		
		command("look "+me->query("id"));
		command("pat "+me->query("id"));
		command("haha "+me->query("id"));
		//me->set(QUESTDIR4+"sword",1);
		me->set("quest/mj/shlf/jueji/pass",1);
		me->set("title",HBBLU+HIW"����ʥ�����������"NOR);
		me->set("mytitle/quest/shlftitle",HBBLU+HIW"����ʥ�����������"NOR);
		me->start_busy(1);
		log_file("quest/shlflianji", sprintf("%8s(%8s) ʧ��%d�κ󣬳�������ʥ����������ء�iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"), me->query("quest/mj/shlf/jueji/fail"),i,me->query("combat_exp")) );
	   }
	   else
	   {
		me->add("quest/mj/shlf/jueji/fail",1);
		command("buddha");
		tell_object(me,HIY"���������޼ɵ�ָ�㣬��Ȼ��˵�������书�İ��أ����Ƕ�ʥ����������ռ�����ȫȻ����Ҫ�졣\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		//me->set("mj/qkdny/ronghe/time",time());
       // me->set("mj/qkdny/ronghe/time",time());
	    me->start_busy(1);
		log_file("quest/shlflianji", sprintf("%8s(%8s) ʥ��������ռ����ؽ���ʧ��%d�Ρ�iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"),me->query("quest/mj/shlf/jueji/fail"),i,me->query("combat_exp")) );
	   }
	 return 1;
	}

}

//����ȭ�ܾ�
int ask_qsqzj() 
{
	int i;
	object me = this_player();
	if(this_object()->is_fighting()) return 0;
	message_vision(HIC"$N��$n����й�����ȭ�ռ��������������\n"NOR, me, this_object());
	if(me->query("family/family_name")!="����"||me->query("family/master_name")!="���޼�")
	{
		command("?");
		command("say �㲻���ҵ��״����ӣ��ѵ�������͵ѧ��");
		command("kick "+me->query("id"));
		return 1;
	}

	if(me->query("quest/mj/qsq/zongjue/pass"))
	{
		command("?");
		command("say ���Ѿ��������������ȭ�����İ��أ��ѵ���������ǲ��������"NOR);
		command("kick "+me->query("id"));
		me->set("title",HBRED+HIW"���˶ϻ�"NOR);
		me->set("mytitle/quest/qishangtitle",HBRED+HIW"���˶ϻ�"NOR);
		return 1;
	}
	command("look "+me->query("id"));	
	//��ͨ�������
	//�������40
	if(me->query("con")<30)
	{
		command("shrug "+me->query("id"));
		command("say ����������̫���ˣ�����30��");
		command("addoil "+me->query("id"));
		return 1;
	}
	if(me->query("quest/mj/qsq/zongjue/fail")>=3 && me->query("registered")<3)
	{
		command("shrug "+me->query("id"));
		command("say �Ѿ���δ��ڣ�����ô����û������,�湻���ģ�");
		command("puke "+me->query("id"));
		return 1;
	}
	//�书ѧϰ֮����Ҫ���һ�죬������Ҫ���50K
	if( time()-me->query("quest/mj/qsq/zongjue/time")<86400)
	{
		command("shake "+me->query("id"));
		command("say �����Ƚ̵�������ɣ�����ɡ�");
		return 1;
	}
	if(me->query_skill("qishang-quan",1)<500)
	{
		command("look "+me->query("id"));
		command("say ���㵱ǰ������ȭ��������500�������»����������򣬻���ץ��ȥ����ȥ�ɡ�");
		return 1;
	}
	
	me->set("quest/mj/qsq/zongjue/time",time());
	me->set("quest/mj/qsq/zongjue/combat_exp",me->query("combat_exp")); 
	i= random(20);
	command("sigh "+me->query("id"));
	command("say ����ȭ�����������������̵�����书����Ȼ����������Ҿ�˵����������������û����������ˡ�");
	command("whisper "+me->query("id")+"������ң��Ҽ�Ϊ����Ϊ��...��");
	command("smile "+me->query("id"));
	
	remove_call_out("thinking_qsq");
	call_out("thinking_qsq",1,me);	
	return 1;
}

int thinking_qsq(object me)
{
	int i,j,total;
	if(!me) return 0;
	
	if(me->query_temp("qsq/ask")<(3+random(3)))
    { 
	  me->add_temp("qsq/ask",1);
      if(random(2)) tell_object(me,HIG"\n����������Ÿղ����޼�������������ȭ������һ��һʽ...\n"NOR);
             else tell_object(me,HIY"\nͻȻ�䣬���ƺ�ץ����ʲô...\n"NOR);
	  tell_room(environment(me),HIC""+me->query("name")+"�ƺ���˼����ʲô��üͷ���塣\n"NOR, ({}));
	  remove_call_out("thinking_qsq");
	  call_out("thinking_qsq",3+random(3), me);
	}
	else
	{  
	  me->delete_temp("qsq/ask");
      total = me->query("str") + me->query("con")+ me->query("dex")+ me->query("int");
      j = 20;
      if(me->query("m-card-vip")) j =  18;
      if(me->query("y-card-vip")) j =  15;
      if(me->query("buyvip"))     j =  10;
	  i= random(j);
	  if(i<3 && random(me->query("kar"))>=25)
	  {
		tell_object(me,HIC"\n�㰴�����޼ɵ�ָ�㣬������ȭ�������ռ������ƺ���Щ�ĵá�\n"NOR);
        tell_object(me,RED"\n���Ȼ��ζ��������ȭ�����ľ�������\n"NOR);
		tell_object(me,HIY"\n�㽫���޼ɽ�������ݺ���ǰ�Լ���ѧ�໥ӡ֤���漴�����̲�ס������Ц��\n"NOR);
		tell_object(me,HIC"\n��ϲ������ǧ����࣬���ڽ⿪����ȭ�����ռ����ء�\n"NOR);
        tell_object(me,HIR"\n���Ѿ�������ȭ�������ռ����س����ڻ��ͨ��\n"NOR);
    
		
		command("look "+me->query("id"));
		command("pat "+me->query("id"));
		command("haha "+me->query("id"));
		//me->set(QUESTDIR4+"sword",1);
		me->set("quest/mj/qsq/zongjue/pass",1);
		me->set("title",HBRED+HIW"���˶ϻ�"NOR);
		me->set("mytitle/quest/qishangtitle",HBRED+HIW"���˶ϻ�"NOR);
		
		log_file("quest/qsqzongjue", sprintf("%8s(%8s) ʧ��%d�κ󣬳�����������ȭ�������ء�iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"), me->query("quest/mj/qsq/zongjue/fail"),i,me->query("combat_exp")) );
	   }
	   else
	   {
		me->add("quest/mj/qsq/zongjue/fail",1);
		command("poke ");
		tell_object(me,HIY"���������޼ɵ�ָ�㣬��Ȼ��˵�������书�İ��أ����Ƕ�����ȭ�������ռ�����ȫȻ����Ҫ�졣\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		//me->set("mj/qkdny/ronghe/time",time());
       // me->set("mj/qkdny/ronghe/time",time());
		log_file("quest/qsqzongjue", sprintf("%8s(%8s) ����ȭ�����ռ����ؽ���ʧ��%d�Ρ�iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"),me->query("quest/mj/qsq/zongjue/fail"),i,me->query("combat_exp")) );
	   }
	 return 1;
	}

}

string ask_was() 
{
	
	object me = this_player(), ob = this_object();
	int max,i;
	int totalexp=0, maxexp, minexp;//��ֹexp���̫��
	object obj1;
	object *ob_list;
	object ob2;
	object fbroom;
	object *team;
	
	
	team = me->query_team();
	
	if (me->query("shen")<0) return "�㻵�������ˣ��Ҳ����İ�������񽻸��㡣";	
	if (me->query("combat_exp")<10000000) return "��������δ�гɣ��Ҳ����İ�������񽻸��㡣";	
	
	 if (me->query("gmd_job/gmdscore"))
    {
	        command("say ���Ȼ�������ɹ��ˣ���Χ�����ҹ�����,����������ϴ�ĸ���ڹ�����������ǰ�õ��Ľ�����");
	        message_vision("���޼�Ҫ���������������,�����Ը�������(answer yes ),��Ը�������(answer no)��\n",me);
			add_action("do_answer","answer");
			me->set_temp("fangqiscore",1);
			return "�ٺ�...";
	}
	
	
	//��������ģʽ
	if (team){		
		
		
		if (team[0] != me) {		
		return "ֻ�ж���������ܽ�����";
	    }
		if (sizeof(team) > 5 ){
		 return "��ȥ�ж������˶࣬�������ӡ�";
		}
		
		maxexp=minexp=team[0]->query("combat_exp");
		
		
		for (i=0;i<sizeof(team);i++){			
			
		totalexp = totalexp + team[i]->query("combat_exp");
		
		if(team[i]->query("combat_exp") > maxexp) {
			maxexp=team[i]->query("combat_exp");
			//maxplayer=team[i];
		}
		else if(team[i]->query("combat_exp") < minexp)
			  minexp=team[i]->query("combat_exp");		
			
			
		if (!team[i]){
			return "��Ķ�����������⣬���ɢ�������齨��";
		}
		
         if (!present(team[i])){			
			return "�ף���ô�����˲�ȫ����"+team[i]->query("name")+"��ôû����";
		}
        
		 if (team[i]->query("gmd_job/gmdscore")) return "��Ķ��������������������ɹſ������¡�";
		 
         if ((int)team[i]->query("shen")<0) 
			return "��Ķ������м���С�ˣ��Ҳ����İ�������񽻸��㡣";		 
		
		 if (team[i]->query("combat_exp")<10000000) 
			 
		 return "��Ķ���������������δ�гɣ��Ҳ����İ�������񽻸��㡣";	
   
		if( team[i]->query_temp("quest/busy")) //added by tangfeng ��quest��ͻ
		{			
			return "���������ڽ���֮�У����ǻ����ȴ����������������˵�ɡ�";
		}
		
		if (team[i]->query("job_name")=="�´�����") //added by tangfeng ��quest��ͻ
		{			
			return "���Ƕ������˸������´����£����ǻ����ȵ����������˵�ɡ�";
		}
		
		if (team[i]->query("job_name")=="������Ħ��") //added by tangfeng ��quest��ͻ
		{			
			return "���Ƕ������˸�������Ħ�£����ǻ����ȵ����������˵�ɡ�";
		}
		
		if (team[i]->query("job_name")=="�����ɹ�����" )
		return "���Ƕ������˸������ɹ���������";
		
		if (team[i]->query_condition("job_busy"))
		{			
			return "���Ƕ������˸�����������Ҫ��Ϣ��";
		}
		
		if (team[i]->query_condition("was_busy"))
		{			
			return "���Ƕ������˸������´�����������Ҫ��Ϣ��";
		}
		if (team[i]->query_condition("killer")) 
			return "��Ķ������б��ٸ�ͨ�����ˡ�";
		
		
		
		if (me == team[i]) continue;
/*
		if (!interactive(team[i]) || query_ip_number(team[i]) == query_ip_number(me)) {
		return "�㻹�ǽ�"+team[i]->query("name")+"���������˰ɡ�;
		}*/

	}
      //if((maxexp-minexp) > 5000000){
		  if (minexp>100000000)
		  {
			  if ((maxexp-minexp)>maxexp*0.1)  return "��ȥ����������ҿ���λ��Ա�������ƺ��޴�������";			
		  }
		  else
		  {
			  if((maxexp-minexp) > 5000000) return "��ȥ����������ҿ���λ��Ա�������ƺ��޴�������";
		  }
			

		
	}  //���
	
	//����
	
	
//	if (!wizardp(me))	
//              return "��ʱ�ر�,������������֪ͨ!";
 if (!wizardp(me))	{
	if (me->query_temp("was_job/asked") )
		return "�㲻���Ѿ��ӹ���������";
	
	if (me->query("job_name")=="�´�����")
		return "��������´��������񣬻���ЪЪ�ɡ�";
	
	if (me->query("job_name")=="������Ħ��") return "������꿹����Ħ�����񣬻���ЪЪ�ɡ�";
	
	if (me->query_condition("was_busy")) return "��������´��������񣬻���ЪЪ�ɡ�";
	
	if (me->apply_condition("gb_job_busy")) return "������꿹����Ħ�����񣬻���ЪЪ�ɡ�";
	
	if (me->query_condition("job_busy"))
		{			
			return "�������������Ҫ��Ϣ��";
		}
	
 }

	ob2 = new("/clone/npc/zhong-shentong");
	if( ob2 ){
		destruct(ob2);
	}	
	
			
	command("say �ҸղŽӵ����̹�����ʹ��ң�ķɸ봫�飬�ɹſ���������ǲ��������ץ������ԭ�������ɸ��֣�����Ѻ�������ڡ�\n" );
	

	me->set_temp("was_job/asked",1);
	me->apply_condition("job_busy", 30);
	me->apply_condition("was_busy", 30);
	me->apply_condition("was_job", 12);		
	command("say �����ڸ������ƣ����Ǳ�����ھȳ����ɸ��֡�\n");
	
	
		
	if (team){
		
		me->set_temp("was_job/team",team);//��¼����		
		
	}  		

	return "������ʿ�в������֣�����ö�����֣��������ֵ���󣬲����󷨣���ȥӪ��(yingjiu)���Բ���ȫ���м��мǡ�";	
	
}

int do_answer(string arg)
{
	object me = this_player();
	if (me->query_temp("fangqiscore")) {
	if (arg=="yes")
	{
		me->set("gmd_job/gmdscore",0);//���gmd����
		message_vision(HIY"$N�����޼ɵ��˵�ͷ��˵��������Ȼ����ˣ���Ը���ĸ�����������\n"NOR,me);
	}
	else
	{
		message_vision(HIY"$N�����޼�ҡ��ҡͷ��˵��������Ȼ����ˣ����ǲ��ܸ��������ˣ���\n"NOR,me);
	}
	remove_action("do_answer","answer");
	me->delete_temp("fangqiscore");
	}
	return 1;
}



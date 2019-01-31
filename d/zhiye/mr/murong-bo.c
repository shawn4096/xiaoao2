// /u/leontt/npc/murong-bo.c  Ľ�ݲ�
// by leontt 1/5/2000
#include "murong-bo.h"

inherit NPC;
inherit F_MASTER;
#include <ansi.h>
string ask_blade();
string ask_armor();
string ask_me();
string ask_me1();
int ask_douzhuan();
int ask_canhezhi();
string *kill_name=({"������","���޼�","���ٳ���","���ȴ�ʦ","������","���ʦ̫","���߹�",});
void create()
{
        object weapon,armor;
        set_name("Ľ�ݲ�",({"murong bo","murong","bo"}));
        set("title","����Ľ����ү��");
        set("nick","�Ա�֮�� ��ʩ����");
        set("long",
              "���������ºų��Ա�֮��������֮��Ĺ���Ľ�ݲ���\n"
              "�����ϴ��Ų���һ����Ц�ݡ�\n");
        set("age", 57);
        set("attitude", "friendly");
        set("no_bark",1);
        set("shen_type", -1);

        set("str", 40);
        set("int", 40);
        set("con", 40);
        set("dex", 40);
        set("per", 27);

        set("max_qi", 39500);
        set("max_jing", 7500);
        set("neili", 39500);
        set("max_neili", 39500);
        set("eff_jingli", 7000);
        set("jiali", 220);
        set("combat_exp", 14000000);
        set("score", 30000);
        set("chat_chance_combat", 80);

        set("chat_msg_combat", ({
                (: perform_action, "blade.daoying" :),
				(: perform_action, "blade.liandao" :),
                (: perform_action, "strike.riyue" :),
			    (: perform_action, "parry.bishen" :),
				(: exert_function, "shenyuan" :),
		}));

        set_skill("xingyi-zhang", 500);
        set_skill("strike", 500);
        set_skill("finger", 500);
        set_skill("dodge", 500);
        set_skill("force", 500);
        set_skill("canhe-zhi", 500);
        set_skill("murong-jianfa",500);
        set_skill("shenyuan-gong", 500);
        set_skill("yanling-shenfa", 500);
        set_skill("douzhuan-xingyi", 500);
        set_skill("parry", 500);
        set_skill("sword", 500);
        set_skill("literate", 300);
        set_skill("murong-daofa", 500);
        set_skill("blade",500);
        set_skill("xingyi-jianzhen",500);

        map_skill("blade", "murong-daofa");
        map_skill("finger", "canhe-zhi");
        map_skill("force", "shenyuan-gong");
        map_skill("dodge", "yanling-shenfa");
        map_skill("parry", "douzhuan-xingyi");
        map_skill("sword", "murong-jianfa");
        map_skill("strike", "xingyi-zhang");

        prepare_skill("strike","xingyi-zhang");

        create_family("����Ľ��",1,"����");

        set("inquiry",  ([
		"name" : "�Ҿ����Ա�֮������ʩ����Ĺ���Ľ�ݲ���\n",
		"here" : "�����������µĲؾ�¥��\n",
		"rumors" : "���Ǹ���������֮�д�������ͷ����ү�����������ѽ��\n",
		"����" : (: ask_blade :),
		"�̲���¶��" : (: ask_blade :),
		"����" : (: ask_armor :),
		"��Ը" : (: ask_me :),
		"������ɮ" : "�����˼������书����������Ϊ���ѵ������ɲ�ľ���,�������ż��Ҳ��������һЩ��Ը.\n",
		"����" : (: ask_me1 :),
		"��ת���ƾ�ѧ" : (: ask_douzhuan :),
		"�κ�ָ��ѧ" : (: ask_canhezhi :),
	]));

        set_temp("apply/damage", 50);
        set_temp("apply/dodge", 40);
        set_temp("apply/attack", 40);
        set_temp("apply/armor", 40);

        setup();
        if (clonep()){
                weapon = unew(BINGQI_D("blade/lvbo-dao"));
                if(!weapon) weapon=new(BINGQI_D("blade"));
                weapon->move(this_object());
                weapon->wield();

                armor=unew("/clone/armor/longpao");
                if( ! armor) armor = new(ARMOR_D("cloth"));
                armor->move(this_object());
                armor->wear();
        }
        add_money("gold", 1);
}

void attempt_apprentice(object ob)
{
	object me  = this_player();

	string name, new_name;
	name = ob->query("name");

	if (present("jiaxin", me)) {
		if (me->query_skill("douzhuan-xingyi",1)<400)
		{
			command("say ��Ķ�ת�������֮���Ȼ��400���������Ͻ��Ȼ�ȥ����ȥ��\n");
			return ;
		}
		destruct(present("jiaxin",me));
		command("say �ðɣ���Ȼ" + RANK_D->query_respect(ob) + "���Ҷ����ż�����Ϊ��" +
			"��������������Ҿ�������ɡ�");

		new_name = "Ľ��" + name[<4..<1];
		ob->set("name", new_name);
		command("say �ӽ��Ժ���ͽ���" + new_name + "��ϣ�����ܰ�Ľ�ݹ�������");
		command("recruit " + ob->parse_command_id_list()[0]);
		command("chat* ����һЦ��˭�� �Ա�֮�� ��ʩ���� ����������");
		command("chat* haha");
	}
	else
		command("say ��Ľ�ݲ����������ͽ!");
	return;
}

void reset()
{
	object ob;

	if (clonep() && (ob = unew(BINGQI_D("blade/lvbo-dao")))) {
		ob->move(this_object());
		command("wield lvboxianglu dao");
	}
	if (clonep() && (ob = unew(ARMOR_D("longpao")))) {
		ob->move(this_object());
		command("wear long pao");
	}
}

string ask_blade()
{
	object blade;
	object me, ob;
	mapping fam;

	me = this_player();
	ob = this_object();

	if (!(fam = this_player()->query("family")) || fam["family_name"] != "����Ľ��")
		return RANK_D->query_respect(this_player())+"�뱾��������������֪�˻��Ӻ�̸��";

	if (this_player()->query("combat_exp") < 150000)
		return RANK_D->query_respect(this_player())+"�����������������²��ܱ�ס��ѱ�����";

	if ( present("lvboxianglu dao", this_player()))
		return RANK_D->query_respect(this_player()) +
			"�̲���¶��ֻ��һ�ѣ����Ҿ��������ϣ�����̰�����ᣡ";

	if ( present("lvboxianglu dao", this_object())) {
		command("give lvboxianglu dao to "+this_player()->query("id"));
		blade = unew(BINGQI_D("blade"));
		if(clonep(blade)){
			blade->move(this_object());
			command("wield dao");
		}
		else{
			blade = unew(BINGQI_D("blade"));
			blade->move(this_object());
			command("wield dao");
		}
		return "������Ϊ��Ľ������Щ����ء��������׳�٣��Ų����Ҷ����һƬ����������̲���¶�����͸���ɣ�";
	}
	return "��Ǹ���������ˣ��ҵ��̲���¶���Ѹ�����ȡ���ˡ�";
}
string ask_armor()
{
        object armor;
        object me, ob;
        mapping fam;

        me = this_player();
        ob = this_object();

        if (!(fam = this_player()->query("family")) || fam["family_name"] != "����Ľ��")
		return RANK_D->query_respect(this_player())+"�뱾��������������֪�˻��Ӻ�̸��";
        if (this_player()->query("combat_exp") < 150000)
		return RANK_D->query_respect(this_player())+"�����������������²��ܱ�ס������ۡ�";
        if ( present("longpao", this_player()))
		return RANK_D->query_respect(this_player()) +
                "����ֻ��һ�������Ҿ��������ϣ�����̰�����ᣡ";
        if ( present("longpao", this_object())) {
        	command("give longpao to "+this_player()->query("id"));
		if(clonep(armor)){
			armor = unew(ARMOR_D("cloth"));
			armor->move(this_object());
			command("wear cloth");
		}
		else{
			armor = unew(ARMOR_D("cloth"));
			armor->move(this_object());
			command("wear cloth");
		}
		return "������Ϊ��Ľ������Щ����ء��������׳�٣��Ų����Ҷ����һƬ������������۾��͸���ɣ�";
	}
	return "��Ǹ���������ˣ��ҵ������Ѹ�����ȡ���ˡ�";
}

string ask_me()
{
        object me = this_player();

	mapping my_fam  = me->query("family");

	if (my_fam["generation"] == 35)
		return RANK_D->query_respect(this_player())+ "���ҹ�������,�ѵ�û���ô�ү������ǲ!";

	if (!(my_fam) || my_fam["family_name"] != "������" || my_fam["generation"] != 36
	 || (string)me->query("class")!="bonze" )
		return RANK_D->query_respect(this_player())+  "�������������书���Ǿ߼�֮��,�㲻֪��Ҳ��.";

	if (me->query_temp("sl_wm1"))
		return RANK_D->query_respect(this_player()) +  "�Ҳ��Ǻ���˵������?�㵱��Ľ�ݲ�ʲ����?";

	me->set_temp("sl_wm1",1);
	return "��ʦ��ż���ᵽ��������ʦ��������ʦ�������ȥѰ��һ����Ħ��ʦ��д�Ľ�վ�,\n"+
		"һȥ��ʮ����������,ʦ����̸���ƺ��йһ�֮��,��Ҳ��ȥ��̽������Ҳûʲ����Ϣ��";
}

string ask_me1()
{
	object me = this_player();

        if ( file_name(environment(this_object())) != this_object()->query("startroom"))
        	return "�����������棬���һ�ȥ��˵�ɡ�";

	if (!present("fanwen jing", me))
		return RANK_D->query_respect(this_player()) + "����û�о���,�������Ĵ�ڿ��?";
	command("nod");
	tell_room(me,HIY "Ľ�ݲ�����һ��,"+ me->name()
		+ "�·����Ƽ���һ��ɽ������ݡ�\n"NOR, ({ me }));
	write(HIY"�����һ���ھ�������������׽������ݡ�\n"NOR);

	me->move("/d/shaolin/liwu");
	return "�������,�����ӷ�.";
}

int ask_douzhuan()
{
	object ob=this_player();
    mapping fam;
	int time;
  

    if (!(fam = this_player()->query("family")) || fam["family_name"] !="����Ľ��"){
		command("? " + ob->query("id"));
        command("say ���뱾��������������֪Ϊ���д�һ�ʣ�");
        return 0;
       }
	if (ob->query("quest/mr/dzxy/pass")) {
		command("? " + ob->query("id"));
		ob->set("title", HIC"��"HIG"ת"HIB"��"HIY"��"NOR);
		command("say �㲻���Ѿ��������еİ�������");
		return 1;
	}
	if (ob->query("sydzxy/fail") >=3 && ob->query("registered") < 3){
		command("hmm");
		command("say ������������,�������������ˣ�");
		return 1;
	}
 	if (!ob->query("mr/qinchuan"))
	{
		command("say �����Ľ�����ҵմ����ӣ����ĺú�����һ�������ٸ����㡣");
		return 1;
	}
	time = time()-(int)ob->query("quest/mr/dzxy/time");

	if ( ob->query("quest/mr/dzxy/time") && time< 86400 ) {
		command("shake");
		command("say �����ʱ��δ��,���Ժ�������");
		return 1;
	}
	if (!ob->query_temp("quest/mr/dzxy/giveguan"))
	{
		command("say �������ľ����Ұ�Ľ�����ҵĻʹڸ�������������������ҡ�\n");
		return 1;
	}
	if (!ob->query_temp("quest/mr/dzxy/givebiao"))
	{
		command("say �������ľ����Ұ�Ľ�����ҵĻʵ���ϵ������������Ҿͽ��㡣\n");
		return 1;
	}
    if ( ob->query_skill("shenyuan-gong",1) < 450) {

		command("shake "+ ob->query("id"));
		command("say ��λ"+RANK_D->query_respect(ob)+"��Ķ�ת�����书���ڸ���,������ɱ������ң����ڻ����Ǹ������ʱ��");
		return 1;
	}
	message_vision(HIC"Ľ�ݲ�˵��������Ľ��һ���˴�������ᣬ����Ľ�ݴ���Ľ�������������¡����ľ���\n"+
	                   "���׶������ֵĶ�ת���ƾ�����������֮�������������Ա�֮����ʩ���������ߺ�\n"+
		               "����һ��,���˼������֡���̾��Ľ��һ������δ�������������ΰҵ����\n "NOR,ob);
	command("sigh ");
	command("shake ");
	command("consider ");
	command("say ��ͼ��ҵ���ս��ɳ�����������ϰ�������񹦣��Ҿʹ��ڸ���ɣ��ܷ�������Ļ�Ե�������ˡ�\n");
	ob->start_busy(999);
	remove_call_out("thinking_xingyi");
	call_out("thinking_xingyi",2,ob);
	return 1;
}

int ask_canhezhi()
{
	object ob=this_player();
    mapping fam;
	string k_name;

	int i, time;
 	(int)time = (int)time()-(int)ob->query("canhe/time");


    if (!(fam = this_player()->query("family")) || fam["family_name"] !="����Ľ��"){
		command("? " + ob->query("id"));
        command("say ���뱾��������������֪Ϊ���д�һ�ʣ�");
        return 0;
    }
	if (ob->query("quest/mr/canhe/pass")) {
		command("? " + ob->query("id"));
		command("say �㲻���Ѿ��������еİ�������");
		return 1;
	}
	if (!ob->query("mr/qinchuan"))
	{
		command("say �����Ľ�������״����ӣ����ĺú�����һ�������ٸ����㡣");
		return ;
	}
	
	if (ob->query("int")< 40) {
		command("? " + ob->query("id"));
		command("say ����������Բ���40�����������ˣ�");
		return 1;
	}
	if (ob->query("canhe/fail") >=3 && ob->query("registered") < 3){
		command("hmm");
		command("say ������������,�������������ˣ�");
		return 1;
	}
	if ( ob->query("canhe/time") && time < 86400 ) {
		command("shake");
		command("say ������Ҳ̫Ƶ���ˣ����Խ���ʱ��δ��,���Ժ�������");
		return 1;
	}

    if ( ob->query_skill("douzhuan-xingyi",1) < 450||ob->query_skill("canhe-zhi",1) < 450) {

		command("shake "+ ob->query("id"));
		command("say ��λ"+RANK_D->query_respect(ob)+"��Ķ�ת�����书���ڸ���,������ɱ������ң����ڻ����Ǹ������ʱ��");
		return 1;
	}
	if (!ob->query("quest/�����˲�/��������ƪ/over"))
	{
		command("heng "+ ob->query("id"));
		command("say ��λ"+RANK_D->query_respect(ob)+"�Ҵ����Ը���Ϊ���Σ�����Ľ�ݵ����޲�Ϊ�˷ܶ��������㶼����ʲô����");
		command("whisper ��λ"+RANK_D->query_respect(ob)+"���������������˲�����ƪ��������ȥɱ��һ�������Ҿ͸�����!");
		
		return 1;
	}
	
	if (ob->query_temp("quest/mr/canhe/give_shouji")<1)
	{
		command("nod ");
		command("whisper " + ob->query("id")+" ����ֻ����ν���˴������̸�����ף�����......");
		command("look " + ob->query("id"));
		command("whisper " + ob->query("id")+" ��������������ν�����С�����һ�֮˵�����������ɡ��䵱�ɡ�ȫ��̡������ɡ���ɽ�ɡ���������ؤ�");
		command("whisper " + ob->query("id")+" �������֡��䵱�˳�����̩ɽ�����������ػ�֮��������������ɮ���������˳Ʋ����Ϲ��");
		command("whisper " + ob->query("id")+" ��ؤ�������µ�һ����ǰ�ΰ������壬������������������ؤ���ߣ���������һ���ĸ��֡�");
		command("consider");
		command("whisper " + ob->query("id")+" �����������޼��ƽ��������̣����������ԭ����֮�ƣ������䵱��ϵ���ܣ�Ӱ��������Ӿ硣");
		command("whisper " + ob->query("id")+" ���ϴ������ٸ������������֣�����������Ϊ�����һ���֣�Ю����֮������Լ��Ϊ��������֮��");
		command("whisper " + ob->query("id")+" ��ˣ�Ҫ�������£�����ɨ���⡰����һ��һ��һ���ҡ����Ը�ؤ�����֣����Ѿ�����һ����ȫ֮�ߡ�");
		command("whisper " + ob->query("id")+" "+ RANK_D->query_respect(ob) +"��Ȼ��־�������£����������ȥɱ�����ˣ�������־��");
		k_name=kill_name[random(sizeof(kill_name))];
		if (k_name=="���޼�")
		{
			if (!ob->query_temp("quest/mr/canhe/kwuji"))
			{
				command("say ��Ȼ��ˣ���������ƴ󣬽�Ӱ���Ҵ��ิ�ˣ�����������ȥ�����޼���С������ͷ������\n");
				ob->set_temp("quest/mr/canhe/kwuji",1);
			}else command("say ���Ų����Ѿ�ɱ�����޼���ô���ټ����ʣ����������ٸ������������");
		
		}else if (k_name=="������")
		{
			if (!ob->query_temp("quest/mr/canhe/ksanfeng"))
			{
				command("say ��Ȼ��ˣ��䵱�������ȵ�𣬽�Ӱ���Ҵ��ิ�ˣ�����������ȥ�������������ݵ��˵���ͷ������\n");
				ob->set_temp("quest/mr/canhe/ksanfeng",1);
			}else command("say ���Ų����Ѿ�ɱ����������ô���ټ����ʣ����������ٸ������������");

		}else if (k_name=="���ʦ̫")
		{
			if (!ob->query_temp("quest/mr/canhe/kmiejue"))
			{
				command("say ��Ȼ��ˣ���ü������˲Ŷ�ʢ����Ӱ���Ҵ��ิ�ˣ�����������ȥ�����ʦ̫���ϱ�̬����ͷ������\n");
				ob->set_temp("quest/mr/canhe/kmiejue",1);
			}else command("say ���Ų����Ѿ�ɱ�����ʦ̫��ô���ټ����ʣ����������ٸ������������");
		}else if (k_name=="���ٳ���")
		{
			if (!ob->query_temp("quest/mr/canhe/kkurong"))
			{
				command("say ��Ȼ��ˣ����������µĿ��ٺܲ����֣���Ӱ���Ҵ��ิ�ˣ�����������ȥ�����ٳ�������ͺ¿����ͷ������\n");
				ob->set_temp("quest/mr/canhe/kkurong",1);
			}else command("say ���Ų����Ѿ�ɱ�˿��ݳ�����ô���ټ����ʣ����������ٸ������������");
		}else if (k_name=="������")
		{
			if (!ob->query_temp("quest/mr/canhe/kmu"))
			{
				command("say ��Ȼ��ˣ����������µĿ��ٺܲ����֣���Ӱ���Ҵ��ิ�ˣ�����������ȥ�����ٳ�������ͺ¿����ͷ������\n");
				ob->set_temp("quest/mr/canhe/kmu",1);
			}else command("say ���Ų����Ѿ�ɱ����������ô���ټ����ʣ����������ٸ������������");
		}else if (k_name=="���߹�")
		{
			if (!ob->query_temp("quest/mr/canhe/khong"))
			{
				command("say ��Ȼ��ˣ�ؤ�������������Ӱ���Ҵ��ิ�ˣ�����������ȥ�����߹�����Ͻл�����ͷ������\n");
				ob->set_temp("quest/mr/canhe/khong",1);
			}else command("say ���Ų����Ѿ�ɱ�˺��߹���ô���ټ����ʣ����������ٸ������������");
		}
		else {

			command("say �Ϸ�����ʹ��ˣ�ûͦ�����������һ����������\n");
			command("say �ⶼ��������������һ��������⡣\n");
		}
		return 1;
	}
	
	message_vision(MAG"Ľ�ݲ��ƺ�����һ�����»���֮�У���̧ͷ����ʱ��ֻ������������һ��ɱ�����ڣ�һ����ã��\n"NOR,ob);
    message_vision(HIY"Ľ�ݲ�����˵����������Ľ���ϵļҴ��书���澫�£�������ƥ��ֻ������ûѧ���Ҷ��ѣ�\n"+
		"�ѵ�����Ͳ�����������ϵġ������񽣡��ˣ�����ϸ�ˣ������ʳָ������������¡�\n"NOR,ob);
	remove_call_out("thinking_canhe");
	call_out("thinking_canhe",2,ob);
	ob->start_busy(999);
	return 1;
	
}


int thinking_canhe(object me)
{
  int i,j,total;
  if(!me) return 0;
	
  if(me->query_temp("canwu_canhe")<(10+random(10)))
  { 
	  me->add_temp("canwu_canhe",1);
      if(random(2)) tell_object(me,HIG"\n����������Ÿղ�Ľ�ݲ���չʾ��һ��һʽ...\n"NOR);
             else tell_object(me,HIY"\nͻȻ�䣬���ƺ�ץ����ʲô...\n"NOR);
	  tell_room(environment(me),HIC""+me->query("name")+"�ƺ���˼����ʲô��üͷ���塣\n"NOR, ({}));
	  remove_call_out("thinking_canhe");
	  call_out("thinking_canhe",3+random(3), me);
   }
   else
   {  
	 
      total = me->query("str") + me->query("con")+ me->query("dex")+ me->query("int");
      j = 25;
      if(me->query("m-card-vip")) j =  20;
      if(me->query("y-card-vip")) j =  17;
      if(me->query("buyvip"))     j =  15;
	  i= random(j);
 
	  if (random(me->query("kar"))>27 
			&& random(me->query("int")) >=40 
			&& me->query("kar") <31
			&& i==1)
		{
			command("look " + me->query("id"));
			command("nod " + me->query("id"));
			command("chat* pat" + me->query("id"));
			command("say �ð�,�Ҿͽ�����Ľ�ݲκ�ָ�������ռ����������ɡ�");
			command("chat ������Ц�����ҹ���Ľ������һ������κ�ָ������������,�γ����ҵ���ɣ�");
			command("chat* laugh");
			log_file("quest/canhezhi",sprintf("%-18sʧ��%s�κ󣬳ɹ���Ľ�ݲ�������κ�ָ�����ľ������ڣ�����%d����%d��\n",
			me->name(1)+"("+capitalize(getuid(me))+")",
			chinese_number(me->query("quest/mr/canhezhi/fail")), 
			me->query("kar"), 
			me->query("int")), me);
			me->set("quest/mr/canhezhi/pass", 1);
			me->set("canhe/pass",1);
			me->set("quest/mr/canhezhi/exp", me->query("combat_exp"));
			me->set("title",HIG"Ľ�ݲκ�ָ����"NOR);
			me->delete_temp("quest/mr/canhe");
			me->delete_temp("canwu_canhe");
			me->start_busy(1);
			return 1;		
		
		}
	    else {
		command("sigh " + me->query("id"));
		command("poor ");
		command("say �����㻹��δ���������а������ڵ�ʱ��,����������!");
		me->add("quest/mr/canhezhi/fail", 1);
		me->set("quest/mr/canhezhi/time", time());
		log_file("quest/canhezhi",
			sprintf("%-18s���Ľ�ݲ�������κ�ָ�����ľ���ʧ�ܣ�ʧ��%s�Ρ�\n",
				me->name(1)+"("+capitalize(getuid(me))+")",
				chinese_number(me->query("quest/mr/canhezhi/fail")) 
			), me
		);
		 me->delete_temp("quest/mr/canhe");
		 me->delete_temp("canwu_canhe");
		 me->start_busy(1);
	  }
  }
   return 1;
}

int thinking_xingyi(object me)
{
  int i,j,total;
  if(!me) return 0;
	
  if(me->query_temp("canwu_xingyi")<(10+random(10)))
  { 
	  me->add_temp("canwu_xingyi",1);
      if(random(2)) tell_object(me,HIG"\n����������Ÿղ�Ľ�ݲ����̸��Ķ�ת���ư���..\n"NOR);
             else tell_object(me,HIY"\nͻȻ�䣬���ƺ�ץ����ʲô...\n"NOR);
	  tell_room(environment(me),HIC""+me->query("name")+"�ƺ���˼����ʲô��üͷ���塣\n"NOR, ({}));
	  remove_call_out("thinking_xingyi");
	  call_out("thinking_xingyi",3+random(3), me);
	}
   else
   {  	 
      total = me->query("str") + me->query("con")+ me->query("dex")+ me->query("int");
      j = 25;
      if(me->query("m-card-vip")) j =  20;
      if(me->query("y-card-vip")) j =  17;
      if(me->query("buyvip"))     j =  15;
	  i= random(j);
 
	  if (random(me->query("kar"))>26 
			&& random(total) >=120 
			&& me->query("kar") <31
			&& i==1)
		{
			command("look " + me->query("id"));
			command("nod " + me->query("id"));
			command("chat* pat" + me->query("id"));
			command("say �ð�,�Ҿͽ�����Ľ�ݶ�ת���Ƶ��ռ����������ɡ�");
			command("chat ������Ц�����ҹ���Ľ������һ������ת���ƾ�������,�γ����ҵ���ɣ�");
			command("chat* laugh");
			log_file("quest/xingyi",sprintf("%-18sʧ��%s�κ󣬳ɹ���Ľ�ݲ�������ת�����ںϵľ������ڣ�����%d����%d��\n",
			me->name(1)+"("+capitalize(getuid(me))+")",
			chinese_number(me->query("quest/mr/dzxy/fail")), 
			me->query("kar"), 
			me->query("int")
		   ), me);
			me->set("quest/mr/dzxy/pass", 1);			
			me->set("quest/mr/dzxy/exp", me->query("combat_exp"));
		    me->set("title", HIC"��"HIG"ת"HIB"��"HIY"��"NOR);
			me->start_busy(1);
			me->delete_temp("canwu_xingyi");
			me->delete_temp("quest/mr/dzxy");
			return 1;	
		
		}
	    else {
		command("sigh " + me->query("id"));
		command("poor ");
		command("say �����㻹��δ�������⶷ת���Ƶİ������ڵ�ʱ��,����������!");
		command("say ��ת�����������µ�һ�ڹ��似����Ҫ������!");
		me->add("quest/mr/dzxy/fail", 1);
		me->set("quest/mr/dzxy/time", time());
		log_file("quest/xingyi",
			sprintf("%-18s���Ľ�ݲ�������ת�����ںϵľ���ʧ�ܣ�ʧ��%s�Ρ�\n",
				me->name(1)+"("+capitalize(getuid(me))+")",
				chinese_number(me->query("quest/mr/dzxy/fail")) 
			), me
		);
		 me->start_busy(1);
		 me->delete_temp("canwu_xingyi");
		 me->delete_temp("quest/mr/dzxy");
	  }
  }
   return 1;
}

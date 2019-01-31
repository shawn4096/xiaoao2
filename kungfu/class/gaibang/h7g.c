// h7g.c ���߹�
// Looklove@SJ 2000/8/25
// Looklove Modify at 2001/1/19
// Looklove Modify at 2001/4/7
// Looklove Modify at 2001/5/3
// River@SJ For ���˭������÷ job 3.29.2002
// Update By lsxk@hsbbs ����ͨ����Ʒ��߽�kanglong���� 2007/7/18
//Update By action@SJ 2008/12/5

inherit NPC;
#include <job_mul.h>
#include <ansi.h>
#include <get_place.h>
#include "h7g.h";

int ask_up();
int pass_chuanwei(object me, object ob);
int ask_kanglong();
string ask_job();
string ask_finish();
string ask_fangqi();

string *no_kill_list = ({
	"mu ren", "jin ren", "yin ren", "zhong shentong", "zhu cong", "shi ren", "huo du","he shiwo"
});

int filldata(object obj1)
{
	if(wiz_level(obj1))
		return 0;
	if(!environment(obj1))
		return 0;
	else return 1;
}

int check(object ob)
{
	object room;
	string room_name;

	if(!objectp(ob)
	 || !ob->query("startroom")      // add by Yuj@SJ to void job NPC
	 || ob->query("env/invisibility")
	 || ob->query("no_quest")
	 || member_array(ob->query("id"), no_kill_list) != -1
	 || userp(ob)
	 || ob->query("attitude")=="aggressive"
	 || ob->query("have_master")
	 || !objectp(room=environment(ob))
	 || room->query("no_fight")
	 || room->query("quest")
	 || room->query("outdoors") == "���ش��"
	 || strsrch(room_name = file_name(room),"/d/") != 0
	 || strsrch(room_name, "/d/wizard/") == 0
	 || strsrch(room_name, "/d/group/") == 0
	 || strsrch(room_name, "/d/wuguan/") == 0
	 || strsrch(room_name, "/d/death/") == 0
	 || strsrch(room_name, "/d/mingjiao/lsd/") == 0
	 || strsrch(room_name, "/d/mingjiao/bhd/") == 0
	 || strsrch(room_name, "/d/gb/") == 0
	 || strsrch(room_name, "/d/shaolin/fumoquan") == 0
	 || strsrch(room_name, "/d/huashan/hamasuperquest") == 0
	 || strsrch(room_name, "/d/baituo/") == 0)
	 return 0;
	return 1;
}

void create()
{
	object ob;
	set_name("���߹�", ({"hong qigong", "hong", "qigong"}));
	set("nickname", HIY"��ָ��ؤ"NOR);
	set("gb/bags",10);
	set("gender", "����");
	set("age", 65);
	set("per",24);
	set("long", "������ؤ���ʮ���ΰ������ųơ���ؤ���ĺ��߹���ү�ӡ�\n");
	set("attitude", "friendly");
	set("no_bark",1);
	set("dgb/wugou",6);

	set("str", 40);
	set("con", 35);
	set("dex", 30);
	set("int", 35);

	set("max_qi", 51000);
	set("max_jing", 9600);
	set("neili", 38500);
	set("max_neili", 38500);
	set("jiali", 250);
	set("eff_jingli", 96000);
	set("combat_exp", 15400000);

	set_skill("force", 530);
	set_skill("huntian-qigong", 550);    // ��������
	set_skill("strike", 530);            // �����Ʒ�
	set_skill("xianglong-zhang", 550);   // ����ʮ����
	set_skill("literate", 200);           // ��д
	set_skill("dodge", 500);             // ��������
	set_skill("xiaoyaoyou", 500);        // ��ң��
	set_skill("parry", 530);             // �����м�
	set_skill("stick", 530);             // ��������
	set_skill("dagou-bang", 530);        // �򹷰���
	set_skill("begging", 200);           // �л�����
	set_skill("checking", 200);          // ����;˵
	set_skill("bangjue", 200);            // ����
	set_skill("dagou-zhen", 530);	     // ����
	set_skill("lianhua-zhang", 500);      // ������
   // set_skill("fengmo-zhang", 500); 
	//set_skill("staff", 500); 
	//set_skill("whip", 500); 
	//set_skill("huifeng-bian", 500); 
	//set_skill("blade", 500); 
	//set_skill("liuhe-dao", 500); 
	//set_skill("", 500); 
	set_skill("stealing", 200);           // hehe

	map_skill("force", "huntian-qigong");
	map_skill("strike", "xianglong-zhang");
	map_skill("dodge", "xiaoyaoyou");
	map_skill("parry", "dagou-bang");
	map_skill("stick", "dagou-bang");
	prepare_skill("strike", "xianglong-zhang");

	set("chat_chance_combat", 90);
	set("chat_msg_combat", ({
		(: perform_action, "strike.xiao" :),
        	(: perform_action, "strike.kanglong" :),
        	(: perform_action, "stick.chan" :),
		(: perform_action, "stick.zhuan" :),
        	(: exert_function, "huntian" :),
        	(: exert_function, "shentong" :),
	}));
	set("chat_chance", 1);
	set("chat_msg", ({
		CYN"���߹�̾�˿�����������������ʱ���ٳԵ��ض����ġ��л�������������\n"NOR,
		CYN"���߹�˵�������϶���Ĺ����ռ������������ҵ����취�Ը�������\n"NOR,
		CYN"���߹��૵���������ؤ��ġ�����ʮ���ơ���������Ե����Ʒ�����\n"NOR,
	}));

	set("inquiry", ([
		/*"�϶���" : "�϶�������ҵ�����ͷ���������˳�������ŷ���塣\n",
		"ŷ����" : "�����ҵ�����ͷ���������˳�������\n",
        	"����" : "���...���...\n",
        	"����" : "�����ҵĺ�ͽ���������˱��˵㡣\n",
        	"����" : "��СѾͷ���Ǹ�����������Ŀ��治����\n",
        	"��ҩʦ" : "����������ѧ��ţ������һ��Ǹ�ϲ�����Ǹ�СѾͷ��\n",
        	"��а" : "����������ѧ��ţ������һ��Ǹ�ϲ�����Ǹ�СѾͷ��\n",
        	"�ϵ�" : "������壬���Ҹ��ʡ�\n",
        	"������" : "�ǿ��Ǹ���ѧ��ţ��Ͻл��ɲ��������ܡ�\n",
        	"����ͨ" : "���������ںܶ�����������������Ϊ�Լ�����������������\n",
        	"ؤ��" : "����ؤ�ﶼ��֪�����ҿ����е��㶷�ˣ�\n",
        	"�򹷰�" : "���...���...������Σ�\n",
        	"������" : "û�±��Ҵ�����С����һ�������㡣\n",
        	"������" : "û�±��Ҵ�����С����һ�������㡣\n",*/
        	//"rumors" : "���û��˵ʲô��Ϣ��\n",
		    "�����л�" : (: ask_kanglong :),
        	"�л���" : (: ask_ji :),
        	"����˫��" : (: ask_wugou :),
        	"��λ":    (: ask_up :),
        	"���˭������÷": (: ask_job :),
        	"job" : (: ask_job :),
        	"finish": (: ask_finish :),
        	"���" : (: ask_finish :),
        	"����" : (: ask_fangqi :),
        	"fangqi" : (: ask_fangqi :),        	
	]));

	create_family("ؤ��", 17, "����");
	set_temp("apply/damage", 70);
	set_temp("apply/dodge", 80);
	set_temp("apply/attack", 80);
	set_temp("apply/armor", 120);
	setup();

	if (clonep()) {		
		object *ob_list = filter_array(users(), (: filldata :));
		for (int i=0;i<sizeof(ob_list);i++){
			if (ob_list[i]->query_temp("gb_chuanwei") ){
				set("long", "������ؤ������ΰ������ųơ���ؤ���ĺ��߹���ү�ӡ�\n");
				set("title","ؤ��ǰ����");
				break;
			}
		}
		ob = unew(BINGQI_D("yuzhu_bang"));
		if (!ob) ob = unew(BINGQI_D("zhubang"));
		ob->move(this_object());
		ob->wield();
		carry_object(ARMOR_D("bainayi"))->wear();
		carry_object(ARMOR_D("shoes"))->wear();
		carry_object(__DIR__"obj/gb_budai10")->wear();
	}
}

void reset()
{	
	if (clonep() ) {
		int i = 0;
		object *ob_list = filter_array(users(), (: filldata :));
		object ob = unew(BINGQI_D("yuzhu_bang"));
		for (i=0;i<sizeof(ob_list);i++){
			if (ob_list[i]->query_temp("gb_chuanwei") ){
				set("long", "������ؤ��İ������ųơ���ؤ���ĺ��߹���ү�ӡ�\n");
				set("title",CYN"ؤ��ǰ����"NOR);
				break;
			}
		}
		if(i==sizeof(ob_list))
		{
			set("long", "������ؤ���ʮ���ΰ������ųơ���ؤ���ĺ��߹���ү�ӡ�\n");
			delete("title");
		}
		if(ob){
			ob->move(this_object());
			command("unwield all");
			command("wield yuzhu bang");
		}		
	}
}
//��ͽ 

void attempt_apprentice(object ob)
{
	if ( ob->query("job_time/ؤ��",1) < 400 && ob->query("job_time/ץ��") < 400){
		command("say  ���ҵĵ���ҪΪؤ�����������" + RANK_D->query_respect(ob) + "�ڰ��еĻ����ƺ�������һЩ��\n");
		return;
	}
	if ( !ob->query("gb/bags") ) {
		command("say " + RANK_D->query_respect(ob) + "������һ��Ҳû�У���������ؤ����Ӱɣ�\n");
		return;
	}
	if ( ob->query("gb/bags")<9) {
		command("say " + RANK_D->query_respect(ob) + "�ڰ���ְλ̫�ͣ��Ȼ��۹��������Ŵ��ɡ�\n");
		return;
    	}
	if ( ob->query_skill("huntian-qigong",1)< 400) {
		command("say " + RANK_D->query_respect(ob) + "�ҵĵ�����Ҫ��ʵ�Ļ��������������������400�����������ҡ�\n");
		return;
    	}
	if ( ob->query("shen")< 2000000) {
		command("say " + RANK_D->query_respect(ob) + "��ؤ��ų����µ�һ��ɵ��ǳ����������������������飬��С��2m���������Ǹɵ����ȥ��\n");
		return;
    	}
	if ( (ob->query("job_time/ؤ��") + ob->query("job_time/ץ��")) < 1000){
		command("say " + RANK_D->query_respect(ob) + "�ڰ��е�ץ�ߺ��ⳤ�ͻ������ϼ�1k���ƺ�������һЩ������������������۷��ڵ��ӡ�\n");
		return ;
	}
	if( (ob->query("job_time/��Ч����")+ ob->query("job_time/��ɱ")+ ob->query("job_time/��Ħ��"))< 400) {
		command("say ��Ȼ����400�α�Ч���ҵ�������ؤ���������������ɣ�"+RANK_D->query_respect(ob)+"Ӧ��Ϊ��Ϊ������㹱�ײź�(400��)��");
		return ;
	}		
	command("chat ���������Ͻл�����֮ǰ�����ҵ�"+ob->name()+"����һ������֮��,ؤ���������ˡ�\n");
	command("recruit " + ob->query("id"));
	ob->set("class", "beggar");
	ob->set("gb/fenduo","�ܶ�");

	if (!ob->query("gb/baih7g")){
		ob->set("gb/baih7g",ob->query("combat_exp"));
		ob->set("title","ؤ����߹��״�����");
	}
	return;
}
//��λ����

int ask_up()
{
	object obj1, me=this_player(),ob=this_object();
	int max, i, skill, bag = me->query("gb/bags");
	mixed *ob_list;

	skill = me->query_skill("xianglong-zhang",1);
	
	if( me->query_temp("gb_chuanwei") ){
		command("say " + RANK_D->query_respect(me) + "�Ѿ���ؤ��������ο��������ҿ���Ц��\n");
		return 1;
	}	
	if( !me->query("gb/bags")){
		command("say " + RANK_D->query_respect(me) + "����ؤ�������������˻���֪�Ӻ�˵��\n");
		return 1;
	}
	if( bag < 9 ){
		command("say ���ڰ��е�λ̫�ͣ���λ��������޷�˵���ڵ��ӡ�\n");
		return 1;
	}
	if ( (me->query("job_time/ؤ��") + me->query("job_time/ץ��")) < 2000){
		command("say " + RANK_D->query_respect(me) + "�ڰ��еĻ����ƺ�������һЩ�����������۷��ڵ��ӡ�\n");
		return 1;
	}
	if( me->query("shen") < 2000000){
		command("say " + RANK_D->query_respect(me) + "��������������2m�����������쵼ؤ��������ӡ�\n");
		return 1;
	}
	
	if(mapp(me->query("job_time")))
		me->set("job_time/��Ч����",me->query("job_time/���ϳ�")+me->query("job_time/��ɱ")+me->query("job_time/��Ħ��"));
	
	if( me->query("job_time/��Ч����") < 500) {
		command("say ��ؤ���������������ɣ�"+RANK_D->query_respect(me)
		+"Ӧ��Ϊ��Ϊ������㹱�ײźá�");
		return 1;
	}		
	if( me->query_skill("dagou-bang",1) < 450 || me->query_skill("xianglong-zhang",1) < 450 ){
		command("say �򹷰����ͽ���ʮ��������ؤ���洫������" + RANK_D->query_respect(me) + "���ⷽ�����Ϊ�Ƿ��Բ���һ�㡣\n");
		return 1;
	}
	if( !present("yuzhu bang",ob) )	{
		command("say �ҵ������������ȥ�ˣ����ˣ����¿�û�취��λ�ˡ�");
		return 1;
	}

	ob_list = users();
	ob_list = filter_array(ob_list, (: filldata :));
	max=sizeof(ob_list);
	for (i=0;i<max;i++){
		obj1 = ob_list[i];
		if (obj1->query_temp("gb_chuanwei") ){
			command( "say ���Ѿ��Ѱ���֮λ����" + obj1->query("name") +"�ˡ�\n" ) ;
			return 1;
		}
	}
	command("look "+me->query("id"));
	command( "say �������²����ȿ�������书��" );

	if ( !pass_chuanwei(me, ob ) ) return 1;
	if ( !pass_chuanwei(me, ob ) ) return 1;
	if ( !pass_chuanwei(me, ob ) ) return 1;
	if ( !pass_chuanwei(me, ob ) ) return 1;
	if ( !pass_chuanwei(me, ob ) ) return 1;
	if ( !pass_chuanwei(me, ob ) ) return 1;
	if ( !pass_chuanwei(me, ob ) ) return 1;

	me->set_temp("title",HIR "ؤ���ʮ�˴�����" NOR);

	command("chat �Ͻл����ս�ؤ�����֮λ����"+me->query("name")+"��������ؤ���������ˡ�");
	message_vision("���߹�����$Nһ���������\n",me);
	me->set_temp("gb_chuanwei",1);
	me->add_temp("apply/strength", random(skill/10));//add up bl ciwei
	present("yuzhu bang", ob)->move(me);
	
	ob->set("long", "������ؤ���ǰ�������ųơ���ؤ���ĺ��߹���ү�ӡ�\n");
	ob->set("title",CYN"ؤ��ǰ����"NOR);
	return 1;
}

int pass_chuanwei(object me, object ob)
{
	COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 1);

	if (!present(me,environment(ob)) || me->query("qi") <= 0
	|| me->query("jing") <= 0 || me->query("jingli") <= 0){
		command("say �书���֮���δ����²�����");
		ob->reincarnate();
		return 0;
	}
	return 1;
}

string ask_job()
{
	object me, ob, *living, target;
	string str, food, food_id_list;
	string *food_name = ({"�������","С�����","Сţ����","�����","����"});
	string *food_id = ({"yanggao zuotun", "xiaozhu erduo", "xiaoniu yaozi", "zhangtui rou", "tu rou"});
	string *food_type;
	object objwhere, obj;
	mapping food_type_list;
	mapping skills;
	string *sk;
	int i, j, x, y, z, p;

	me = this_player();

	if (me->query("menggu"))
		return "�ߣ����������ɹţ�������ʲô��";

	if (me->query_temp("potjob/job") && !wizardp(me))
		return "�ţ��Ҳ��Ǹ��������𣬿�ȥȡԭ�ϰ��������������ˣ�";

//	if (me->query("job_name") == "" && !wizardp(me))
//		return "�����ڲ������㻹����ȥ��Ϣһ��ɡ�";

	if (me->query("combat_exp") < 100000 )
		return "��λ" + RANK_D->query_respect(me) + "�书δ�ɣ�����ȥ�����������Ͻл����ҿɲ�̫���ġ�";

	skills = me->query_skills();
	if (mapp(skills)){
		sk = keys(skills);
		for (i=0; i < sizeof(sk); i++)
			if (skills[sk[i]] > (me->query("max_pot") - 90) && sk[i] != "beauty" && SKILL_D(sk[i])->type2() != "worker")
//			if (skills[sk[i]] > (me->query("max_pot") - 90) && SKILL_D(sk[i])->type() != "knowledge" && SKILL_D(sk[i])->type2() != "worker")
				return "���"+to_chinese(sk[i])+"�ȼ������ˣ��޷�������������ˡ�";
	}

	if ( me->query("potential") >= me->query("max_pot") && !wizardp(me))
		return "��λ" + RANK_D->query_respect(me) + "��Ǳ���Ѿ���ô���ˣ�������ȥ���������ɣ�";

	if ( me->query_condition("job_busy") || me->query_condition("pot_job"))
		return "�����ڲ������㻹����ȥ��Ϣһ��ɡ�";

	me->delete_temp("potjob");
	command("say �⡸���˭������÷���ǻ������СѾͷƬ�������Ͻл��ӳԵ�һ���ˣ�\n"+
		"��ƭ���Ͻл��ӽ��˹����Ǹ�ɵС��һ�׽���ʮ���ơ������˵����Ҳ�򵥣�����������\n"+
		"С����ƴ�ɣ�һ����������Σ�һ����С����䣬һ����Сţ���ӣ�����һ����������\n"+
		"��������һ�𡣲�˵�ˣ���˵�ˣ���ˮ�������ˡ�");

	command("taste");

	for(z=0; z < 5; z ++){
		me->set_temp("potjob/food_type/"+ food_name[z], food_id[z]);
	}

	food_type_list = me->query_temp("potjob/food_type");

	y = random(4) + 2;
	for (x = 0; x < y; x ++){
		living = livings();
		for (i=0;i < sizeof(living);i++){
			j = random(sizeof(living));
			if (!j || j == sizeof(living) -1) continue;
			if(check(living[j]) ){
				target = living[j];
				objwhere = environment(target);
				str = objwhere->query("short");
				if (!sizeof(objwhere->query("exits"))
				|| str == "��ɮ��"
				|| str == HIR"������"NOR
				|| str == "ɮ��"
				|| str == "��Ϣ��"
				|| str == "����"
				|| str == "���"
				|| str == "Ů��Ϣ��"
				|| str == "����Ϣ��"
				|| str == "��շ�ħȦ" ) continue;
				if( get_place(base_name(environment(target)))!="" ) break;
			}
		}

		if( !target )
			return "��������ʱ���������㻹����ȥ��Ϣһ��ɡ�";

		p = random(sizeof(food_name));

		food = food_name[p];
		food_id_list = food_id[p];

		food_type = me->query_temp("potjob/type");

		if ( ! sizeof(food_type))
			me->set_temp("potjob/type", ({ food }));
		else {
			for(z=0; z < 5; z ++){
				if (member_array(food, food_type) != -1) {
					food = food_name[z];
					food_id_list = food_id[z];
				}
			}
			food_type = sort_array(food_type + ({ food }), 0);
			me->set_temp("potjob/type", food_type );
		}
		ob = new(__DIR__"pot_target");
		ob->set_temp("target", me);
		ob->set_temp("food_name", food);
		ob->set_temp("food_id", food_id_list);
		ob->move(objwhere);
		for (i=0; i<5; i++)
			ob->random_move();
		obj = new(__DIR__"obj/pot_food");
		obj->set_name(food, ({ food_id_list }));
		obj->set("long", "����һ��"+obj->query("name")+"��������ζ������\n");
		obj->set_temp("food_id", food_id_list);
		obj->move(ob);
		if (me->query_temp("potjob/food_type/"+food))
			me->delete_temp("potjob/food_type/"+food);
		if (strsrch(file_name(environment(ob)), "/d/zhiye/") >= 0
		 || strsrch(file_name(environment(ob)), "/d/group/") >= 0){
		 	if ( environment(ob)->query("outdoors"))
				me->set_temp("potjob/pot_job_place/"+ ob->query("name"), environment(ob)->query("outdoors")+environment(ob)->query("short"));
		 	else if ( environment(ob)->query("indoors"))
				me->set_temp("potjob/pot_job_place/"+ ob->query("name"), environment(ob)->query("indoors")+environment(ob)->query("short"));
			else me->set_temp("potjob/pot_job_place/"+ ob->query("name"), environment(ob)->query("short"));
		}
		else me->set_temp("potjob/pot_job_place/"+ ob->query("name"), get_place(base_name(environment(ob)))+environment(ob)->query("short") );
		me->set_temp("potjob/for_menu/"+ ob->name(), food);
		command("whisper "+ me->query("id")+" ��˵"+ me->query_temp("potjob/pot_job_place/"+ob->query("name")) +GRN"��"+ob->name()+"������"+food+"�������ȥ�����ɣ�");
	}

	me->set_temp("potjob/do_time", y);
	me->set_temp("potjob/time", uptime());
	me->set_temp("potjob/job",1);
	me->apply_condition("pot_job", 6);
	me->apply_condition("job_busy", 6);

	if ( !present("hong's menu", me)){
		new(__DIR__"obj/pot_paper")->move(me);
		message_vision("$N����$nһ������������������˭������÷���Ĳ��ס�\n", this_object(), me);
	}

	p = sizeof(keys(food_type_list));

	if ( p > 0 ){
		for(z=0; z < p; z ++){
			food = keys(food_type_list)[z];
			food_id_list = values(food_type_list)[z];
			obj = new(__DIR__"obj/pot_food");
			obj->set_name(food, ({ food_id_list }));
			obj->set("long", "����һ��"+obj->query("name")+"��������ζ������\n");
			obj->set_temp("food_id", food_id_list);
			obj->set_temp("job_id", me);
			obj->move(me);
			me->set_temp("potjob/be_get/"+food, 1);
		}
		return "�������Ѿ���Щԭ�ϣ��ȸ��㣬�������ȥ�Ұɣ�";
	}
	else
		return "����������ʲôԭ�϶�û�У������ٰ��������ɡ�";
}

string ask_finish()
{
	object me = this_player();
	object ob;
	int pot, i, times;

	if ( !me->query_temp("potjob/job"))
		return "���н���ȥ��ʲô�������ʲô����";

	if ( !me->query_temp("potjob/finish"))
		return "���������ˣ���";

	if ( ! ob =(present("yudi luomei", me)))
		return "������ˣ���ô�����أ�";

	destruct(ob);
	message_vision(HIY"$N�ӹ�$n���ġ����˭������÷�����������������ϣ���Ц�������տɴ󱥿ڸ��ˡ�\n"NOR, this_object(), me);

	command("pat "+ me->query("id"));
	i = me->query_temp("potjob/do_time");
	pot = 50 + i * 100 + random(50);
// �Ժ�ȥ��
	if( me->query("max_neili") < 3500)
		pot += pot/2;
		
       	//�������ƿ�ʼ
        if (me->query("registered")==3){
            		pot = pot * H7G_JOB_MUL * VIP_MUL /10000;
		}
		else
		{
           		pot = pot * H7G_JOB_MUL /100;
		}
		//�������ƽ��� 


	tell_object(me, HIW"���߹�ָ������һЩ��ѧ�ϵ��Խ�������"+chinese_number(pot)+"��Ǳ�ܡ�\n"NOR);
	times = uptime() - me->query_temp("potjob/time");
	me->delete_temp("potjob");
	me->add("potential", pot);
	me->add("job_time/���߹�",1);
	GIFT_D->check_count(me,this_object(),"���߹�");
	log_file("job/zuocai", sprintf("%8s%-10s ������ˣ��õ�%3d��Ǳ�ܣ�ʱ�䣺%d",
		me->query("name"), "("+me->query("id")+")", pot, times), me);
	return "�������´�������С�Ӹ��Ͻл������ˡ�";
}

string ask_fangqi()
{
	object me = this_player();
	object meat1, meat2, meat3, meat4, meat5, meat6;
	meat1 = present("yanggao zuotun", me);
	meat2 = present("xiaozhu erduo", me);
	meat3 = present("xiaoniu yaozi", me);
	meat4 = present("zhangtui rou", me);
	meat5 = present("tu rou", me);
	meat6 = present("yudi luomei", me);

	if ( ! me->query_temp("potjob/job"))
		return "���н���ȥ��ʲô�������ʲô����";

	if ( meat1 ) destruct(meat1);
	if ( meat2 ) destruct(meat2);
	if ( meat3 ) destruct(meat3);
	if ( meat4 ) destruct(meat4);
	if ( meat5 ) destruct(meat5);
	if ( meat6 ) destruct(meat6);

	command("nod "+ me->query("id"));
	me->delete_temp("potjob");
	return "��Ȼ�����ˣ�Ҳ�Ͳ���ǿ���ˡ�";
}

void dest(object obj)
{
	if(!obj) return;
	destruct(obj);
}
//���������
int accept_object(object me, object obj)
{
	object ob_yzz, ob = this_object();
    object ob_yywzk;

	if (obj->query("food_supply") <= 0) return 0;
	if ((string)obj->query("name") != "�л���" || me->query_temp("marks/get-ji")){
		command("say �Ͻл���" + (string)obj->query("name") + "ûʲô��Ȥ����");
		return 0;
	}
	if (query("food") >= (max_food_capacity() - obj->query("food_supply"))){
		command("say �Ͻл����ڱ��úܡ�");
		return 0;
	}
	command("say ����������������ԵĽл���ѽ��");
	command("eat ji");
	command("say �벻����СС��ͣ���˼ȴ��ϸ���͸�������ض�һ����");
	call_out("dest", 1, obj);

	if (!me->query("gb/bags")){
		command("say �㻹���������ʲô��");
		return 1;
	}
	if( ob_yzz = present("yuzhu bang", ob) ){
		ob_yzz->move(me);
		command("say �����������Ҷ����ˣ����͸�����������ɡ�");
		return 1;
	}
	else{
		if( (time()-me->query("gb/jitime")) >= 100 ) {
			me->add("combat_exp",random(200));
			me->add("potential",random(100));
			if(me->query("potential")>me->query("max_pot"))
				me->set("potential",me->query("max_pot"));
			me->set("gb/jitime",time());
		}
		if ( me->query("combat_exp") <= 2000000 ){
			command("say �����ڹ���̫�������Ժ��������������Ұɡ�");
			return 1;
		}

       if ( ! ob_yywzk =(present("yuanyang wuzhenkuai", me))){
           if ( !random(10)
		&& me->query_skill("xianglong-zhang", 1) >= 200
		&& !me->query("xlz/hang")
		&& !me->query_temp("xlz/hang"))
			call_out("kanglong", 10, me, ob);
       }
       else{
           if ( !random(3)
           && me->query_skill("xianglong-zhang", 1) >= 200
           && !me->query("xlz/hang")
           && !me->query_temp("xlz/hang"))
                   call_out("kanglong", 10, me, ob);
           message_vision(HIY"$NͻȻ������������һ����������ͷһ��������$n��Ȼ���ڿ���$N��"HIW"ԧ"HIM"��"HIY"��"HIG"��"HIC"��"HIY"��������\n"NOR, me, this_object());
           command("xixi "+me->query("id"));
           destruct(ob_yywzk);
       }
		return 1;
	}
	return 1;
}

int ask_kanglong()
{
   
    object me,ob;
	int i,j;
	
	me=this_player();
	ob=this_object();
	
	if (!me->query("xlz/hang"))
	{
	   command("say ����ȥ��ɳɽ��������Ϊ��������ζ�����Ŀ��ƺͰ��գ����Ȼûͨ����\n");
	   return 1;
	}
    if (me->query("kanglong/pass"))
	{
	   command("say ���Ѿ������˽��˿����лڵİ��أ��ٺ��ִ���ƨ�ɡ�\n");
	   return 1;
	}
    if (time()-(int)me->query("xlz/kanglong/time")<86400)
	{
	   command("say ʱ�䲻����������̫�ڿ��ˡ�\n");
	   return 1;
	}
	
	message_vision(CYN"\n\n���߹���ȻһЦ����ͽ���������������ӹǻ������أ���Ȼͨ������ɳɽ����������������\n"NOR, me,ob);
	message_vision(HIG"\n\n$Nֻ����$n��$N�����������Լ����⽵��ʮ�����п����лڵİ���ܷ�����Ϳ����Լ����컯�ˡ�\n"
			              +"�����գ��ҽ���һ�С������лڡ��������ˣ���\n"
					+HIY"\n\n˵��$n����΢�����ұ����䣬���ƻ��˸�ԲȦ������һ����������ȥ������ɨ����ǰһ������������һ�죬����Ӧ�ֶ��ۡ�\n"NOR,me,ob);
	message_vision(HIC"\n\n$n����������������ģ�����ǻ��ˣ���Ȼ���������ܡ�ѧ��һ�У��Ѿ�����Ҫ�Է����޿��ˣ����޿��ã���һ�г�ȥ������һ�£�\n"
	                       +"���˾�������һ���군�󼪡������°���ʽ�������飬�ְ��ھ�����֮������������֮��������ϸϸ������һͨ����ֻ�̵�һ�У�\n"
						   +"ȴҲ����һ����ʱ������\n"
						   +"\n\n\n$n��$N��ϰ�Ĳ���Ҫ�죬��˵��������������Ҫ���ܷ������գ��������ظ����������������Ƶ����������Ʒ���˫�ġ�����ʮ���ơ�����\n"NOR,me,ob);
	
	message_vision(HIR"\n\n$N����ʽ�ӣ�����һ���ر�ϸС��������ѧ��$n�����ƣ���׼���ɣ����ľ���һ�ơ����������˼��Σ����ǲ��ϡ�\n"
	                 +HIB"\n\n$n�������ɵС�ӣ���ҡ��������ô��׽����ô�����ɹ�ô����$N����˵������ͨ�죬ڨڨ��Ц�š����߹�����\n"
					 +"�Ҷ���˵����Ҫ�̶Է����޿��ˣ����޿��á���ղ���һ�ƣ�������������������һҡ���Ͱ���ľ��������ˡ�\n"
					 +"����ѧ�������������Ȼ������һ�ƶ�������\n"NOR,me,ob);
	  i = 18;
      if(me->query("m-card-vip")) i =  17;
      if(me->query("y-card-vip")) i =  14;
      if(me->query("buyvip"))     i =  10;
      if (random(me->query_int(1))>40) i=8;
	  i=random(i);
	

	//Խ����ѧϰԽ�졣����
	j=random(me->query("kar"));
	if (me->query("kar")<31
		&&j>=23
		&&i<3)
	{
       message_vision(HIC"\n\n$N��Ȼ���򣬻�Ȼ��������Ҫ�ž���죬ʹ�Է��������ֵ��������߹����۵������ɲ���ô���ǻ���˵��\n"
	   +"����ͷ�󺹵�������ô�ã�ԭ��������ǳ��������ͨ�����汿�õ������Ѽҡ���\n"
	   +"\n\n$n�ֵ�������һ�н����������лڡ����Ʒ��ľ�Ҫ���ڡ������ֶ��ڡ��ڡ��֡�����ֻ����ͺ�����\n"
	   +"����������ֻҪ�м��ٽ�������˭����ʹ�ˡ����������̻ܽ�ҩʦ������������лڣ�ӯ���ɾá���\n"
	   +"����з��������ա����ȥ��������ʮ�֣��������������ȴ���ж�ʮ�֡���һ������ᵽ���⡮�ڡ���ζ����\n"
	   +"��һ�о�����ѧ�������ɡ��ñȳ������ƣ��Ͽڲ�������ȴ�Ǵ����ޱȣ��Ǳ�����������ڡ��֡���\n"NOR,me,ob);
	    message_vision(HIR"\n\n��ϲ�㣡�����������˽���ʮ���Ƶľ����似��ϰ�ÿ����лھ�����\n"NOR,me);
	  command("chat* haha"+me->query("id"));
	   command("chat "+me->query("name")+"������ô��ʱ�����������˿����лڣ��湻���ġ�");
	   command("chat "+"ؤ�ｵ��ʮ����������������Ե����Ʒ�,����֮һ���ڿ����лڡ�");
	   command("chat* congra"+me->query("id"));
	   command("chat "+"��а���������ϵۡ���ؤ������ͨ���������������ͽ����ǧ���������Ҵ�ؤ������磡");	   
	  
	   log_file("quest/xlzkanglong",sprintf("%s(%s) ����ɳɽ�����󣬵õ����߹�������ָ�㿺���лڡ���Դ��%d���������%d��ʧ�ܣ�%d������ֵ��%d��\n",
			me->name(1), me->query("id"),j,i,me->query("xlz/kanglong/fail"),me->query("combat_exp"),me));
	   
	   me->set("kanglong/pass",1);
	   me->set("title",HIY"���߹��մ�����"NOR);
	   return 1;
	}
	else
	{
		message_vision(HIC"\n\n$N��Ȼ�����߹�˵�˿����лڵľ�Ҫ�����������ʹ�õľ�������һʱ֮��ȴ��������⡣����ʮ���Ƶ�\n"
		+"������û�з��ӳ����������㻹���д������¸����߹�ѧϰ�ˡ�\n"NOR,me,ob);
		log_file("quest/xlzkanglong",sprintf("%8s%-10s�õ����߹�������ָ�㿺���лڣ�����û�гɹ�������Ŭ������Դ��%d���������%d��ʧ�ܣ�%d������ֵ��%d��\n",
			me->name(1), me->query("id"),j,i,me->query("xlz/kanglong/fail"),me->query("combat_exp"),me));
		me->add("xlz/kanglong/fail",1);
		me->set("xlz/kanglong/time",time());
		return 1;
	}     
   
}

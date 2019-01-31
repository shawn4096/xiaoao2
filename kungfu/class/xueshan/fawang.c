// by iceland

inherit NPC;
inherit F_MASTER;
#include <ansi.h>

#include "cike.h";
int give_lun();
int give_lun2();
string wulun_dazhuan();
string* luns = ({
       BINGQI_D("gold-falun"),
       BINGQI_D("silver-falun"),
       BINGQI_D("bronze-falun"),
       BINGQI_D("iron-falun"),
       BINGQI_D("leaden-falun"),
});


void create()
{
        object weapon;
        set_name("���ַ���", ({ "jinlun fawang", "jinlunfawang","fawang" ,"jinlun"}));
        set("long",@LONG
����ĸ��ݣ��������ݣ�˫Ŀ������������̫��Ѩȴ�߸�͹���������ࡣ
���ܷ⡰�ɹŹ���һ��ʦ��������һ��ͨ�쳹�ص��񹦡�
LONG
        );
        set("title", HIY "�ɹŹ���һ��ʦ" NOR);
        set("gender", "����");
        set("class", "huanxi");
        set("age", 65);
        set("attitude", "friendly");
        set("shen_type", -1);
        set("str", 40);
        set("int", 30);
        set("con", 30);
        set("dex", 34);
        set("per", 22);

        set("max_qi", 39500);
        set("max_jing", 6500);
        set("eff_jingli", 7500);
        set("neili", 48000);
        set("max_neili", 48000);
        set("jiali", 250);
        set("combat_exp", 13500000);
        set("score", 28000);
        set("unique", 1);
		set("lx/gree",11);
		set("quest/dls/longxiang/pass",1);
		set("quest/wulun/pass",1);

        set_skill("mizong-fofa", 200);
        set_skill("literate", 200);
        set_skill("force", 530);
        set_skill("longxiang-boruo", 530);
        set_skill("dodge", 500);
        set_skill("yuxue-dunxing", 500);
        set_skill("hammer", 530);
        set_skill("xiangfu-lun", 530);
        set_skill("hand", 500);
        set_skill("dashou-yin",500);
        set_skill("claw", 500);
        set_skill("tianwang-zhua", 500);
        set_skill("parry", 500 );

        map_skill("force", "longxiang-boruo");
        map_skill("dodge", "yuxue-dunxing");
        map_skill("hammer", "xiangfu-lun");
        map_skill("parry", "xiangfu-lun");
        map_skill("hand","dashou-yin");
        map_skill("claw","tianwang-zhua");

        prepare_skill("hand","dashou-yin");
        prepare_skill("claw","tianwang-zhua");

        create_family("������", 10, "����");
        set("inquiry", ([
                "����" : (: give_lun  :),
			    "���ִ�" : (: wulun_dazhuan  :),
                "����" : (: give_lun  :),
                "�����" : (: give_lun2  :),
                
       ]));
        set("lun_count",5);
        set("lun_count2",1);
        set("class", "huanxi");
        set("chat_chance", 2);     
        set("chat_msg", ({
		CYN"���ַ�����Ȼ������ʮ����������������ڻ��ͨ���������������ǵڶ��ˣ�\n"NOR,
		CYN"���ַ����߷ߵĵ�����ԭ���˲�����أ������˶࣬��������һӵ���ϡ�\n"NOR,
		CYN"���ַ����߷ߵĵ�: �ߣ�����ƾ��һ��֮������ȡ����������֮λ��\n"NOR,
	}) );
        set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
                (: exert_function, "shield jinlun fawang" :),
                (: perform_action, "hammer.wushuai" :), 
	}));
        set_temp("apply/damage", 70);
        set_temp("apply/dodge", 80);
        set_temp("apply/attack", 60);
        set_temp("apply/armor", 60);

        setup();
	if (clonep()){
                weapon = unew(BINGQI_D("gold-falun"));
                if (!weapon) weapon = unew(BINGQI_D("silver-falun"));
                if (!weapon) weapon = unew(BINGQI_D("bronze-falun"));
                if (!weapon) weapon = unew(BINGQI_D("iron-falun"));
                if (!weapon) weapon = unew(BINGQI_D("leaden-falun"));
                weapon->move(this_object());
                weapon->wield();
                carry_object("/d/xueshan/npc/obj/longxiang-jiasha")->wear();       
                add_money("gold",2);
        }
}

void reset()
{
	set("lun_count2", 1);
}

void attempt_apprentice(object ob)
{
       if ((string)ob->query("family/family_name") != "������") {
                command("say"+ RANK_D->query_respect(ob) +
                        "���Ǳ��ɵ��ӣ������ﵷʲô�ң���");
                return;
        }

        if ((int)ob->query_skill("longxiang-boruo", 1) < 350) {
                command("say �Ҵ����¸����书�����ڹ��ศ��ɡ�");
                command("say"+ RANK_D->query_respect(ob) +
                        "�ٰ�����ͨ��������������б��ŵ��ڹ��ɡ�");
                return;
        }
        if( (string)ob->query("gender") == "����" ){
                command ("say ʩ�������ȱ����˵�����ն�����������...");
                return;
        }

        if( (int)ob->query_con(1) < 30) {
               command("sigh");
               command("say"+ RANK_D->query_respect(ob) +"�����̫������˸����");
               command("shake");
               return;
        }

        if (!(int)ob->query_temp("win_deb")){
                command ("say �㻹�������ҵ��Ӵ�������������Ϊ�ɡ�\n");
                return;
	} 
        command("say ��Ҳ������Ѱһ�������ϼѵĵ��������²����㲻�˼����������Ϊʦ��");
        if (!ob->query("fawang")){
		command("chat* ����˵�����ã�"+ ob->query("name") + RANK_D->query_respect(ob) + "����˫ȫ���ɴ����²���\n");
		command("chat* ���쳤Ц�����������������꣬�����ҵ����ˣ�����֮�����޺��ӣ���");
	}
	command("recruit " + ob->query("id"));
	ob->set("fawang", 1);
	ob->set("title",  "�����½��ַ������µ���"  );
}

int give_lun()
{ 
	mapping fam; 
	object me, ob,lun;

	me = this_object();
	ob = this_player();
       
	if (ob->query_temp("give_lun") == 1){
		command("say �㲻�Ǹմ������������������㵱�Ұ׳հ���");
		return 1;
	}
	if (!(fam = this_player()->query("family")) || fam["family_name"] != "������"){
		command("say ���뱾��������������֪�˻��Ӻ�̸��");
		return 1;
	}
	if ( objectp(present("iron falun", (ob))))  { 
		command("say �����ϲ����Ѿ���������");
		return 1;  
	} 
	if ( objectp(present("iron falun", environment(me)))){ 
		command("say ���ϲ�����ֻ���������۾�Ϲ������");
		return 1;
	} 
      
	if(query("lun_count") < 1){
		command("say �������ˣ�����������û���ֹ���ʹ�á�");
		return 1;
	}
	add("lun_count",-1);       
	lun = unew( luns[random(sizeof(luns))] );
	if(clonep(lun)){
		lun->move(ob);
		command("say �ðɣ���ֻ�������û�ȥ�ú����С�");
		ob->set_temp("give_lun",1);
		message_vision("$N����$nһֻ���֡�\n", me, ob);
		return 1;
	}
	command("say �������ˣ���ʱ�����û�ж���ķ��ֿ��Ը����ˡ�");
	return 1;
}

int give_lun2()
{ 
	mapping fam; 
	object me, ob,lun2;

	me = this_object();
	ob = this_player();
       
	if (!(fam = this_player()->query("family")) || fam["family_name"] != "������"){
		command("say ���뱾��������������֪�˻��Ӻ�̸��");
		return 1;
	}
	if ((int)ob->query_skill("longxiang-boruo", 1) < 200) {
		command("say �Ҵ����¸����书�����ڹ��ศ���, ���������Ϊ�������Ҳ����İѱ��ɱ��ｻ���㡣");
		return 1;
	}
      
	if(query("lun_count2") < 1){
		command("say �������ˣ�����������û�з���ֹ���ʹ�á�");
		return 1;
	}
	add("lun_count2",-1);       
	lun2 = unew(BINGQI_D("bestfalun"));
	if( clonep(lun2)){
		lun2->move(ob);
		command("say �ðɣ����Ǳ���֮������֣����û�ȥ�ú�������������š�");
		message_vision("$N����$nһֻ����֡�\n", me, ob);
		return 1;
	}
	command("say �������ˣ�������Ѹ����ʦ��ȡ���ˡ�");
	return 1;
}

string wulun_dazhuan()
{ 
	mapping fam; 
	object me, ob;
	int i,j,time;

	ob = this_object();
	me = this_player();
       
	
	if (!(fam = this_player()->query("family")) || fam["family_name"] != "������"){
		command("say ���뱾��������������֪�˻��Ӻ�̸��");
		return "";
	}
	

	if( me->query("quest/wulun/pass") )
	{
		
		me->set("title",HIC"��������"NOR);
		me->set("mytitle/quest/wlmwtitle",HIC"��������"NOR);
		return RANK_D->query_respect(me) + "�����Ѿ��������������quest���ֺιʿ�����Ц�أ�";
	}
    if( me->query_skill("xiangfu-lun", 1) < 350 )
		return RANK_D->query_respect(me) + "����Ľ��������費�������޷������������ִ�ת�ľ�Ҫ���ڣ�";

	time = time() - me->query("quest/wulun/time");
	if( me->query("quest/wulun/time") && time < 86400 && !wizardp(me) )
		return "�ţ��㲻�Ǹ�����̹������ִ��𣿻�����Ŭ����ʱ��ɣ�";

	//if( me->query_temp("quest/wulun/pass") )
	//	return RANK_D->query_respect(me) + "���ҸղŲ����Ѿ��ش�������";
    
	message_vision(CYN"$N����Ŀ���$n������˵���������ɵ����ִ󷨽������������ֳ������־���ǧ����̬֮�������һ������ѭ������֮�ƣ�\n"
	"�㿴���ˣ��Ҹ�����ʾһ�飬�����Լ��������ˡ�\n"+
	HIY"���ַ������������������������������磬Ѹ���ޱȡ�����$n�ۻ�����\n"+
		HIR"��������ڿ��ж������죬�������ӣ��ƺ������������������󳪣��㲻���о���Щͷ��.\n"
	HIB"��Ȼ�����ַ���˫�ֲ��ϲٿأ�������ӽ����ɺ�һ̬֮��������ȥ����Ѹ�͡�\n"
	HIC"�㲻�����������ҡ�������ִ󷨵�������Ȼ��˾��ˣ�"NOR, ob, me);

    j = 20;
	if(me->query("m-card-vip")) j =  18;
	if(me->query("y-card-vip")) j =  15;
	if(me->query("buyvip"))     j =  10;
	i=random(j);
	
	command("say �������ִ�Ψ�к������������֮������Ϸ��ܷ��������������һ����ǧ��Ҫ��ס��\n");
	command("pat "+me->query("id"));
	if(i<3 && random(me->query("kar")) >= 27 ) //�����Ѷȣ���Ϊһ�ž���//���������ø��������
	{
		tell_object(me,HIY"\n�����˽��ַ�����ָ�㣬�����ִ󷨵İ��������ĵá�\n"NOR);
		tell_object(me,HIG"\n����ͼ����Ϣ�嵽�͹�Ѩ�У�ͻȻֻ������������һ������ֱͨ˫�֣����е����Ӳ�����Ȼһ�ᡣ\n"
			             +"������ʶ�ؽ�������б�Ϸ���ȥ��һ������֮�������������ƺ������������Ƶã����л���һ�����������ߡ�\n"
						 +"Ȼ������Ȼ�ص�������У����������������ž��������÷��š����д�ϲ֮�£��������½�������˳�ȥ��\n"
						 +"һ����������ǰ����֮��ȫ����˵�����ĳ������á������������һ��ͨ��ʱ���Ǽ��ѣ��ζ�������ͨ����·��\n"
						 +"�ˣ��ڶ��Ρ�������ʱ��Ȼ��Ȼ�ķɿ����䣬���֮�䣬��ǳ���������ʹ��һʮ�˴Ρ�\n"NOR);
		me->set("quest/wulun/pass",1);
		me->set("title",HIC"��������"NOR);
		me->set("mytitle/quest/wlmwtitle",HIC"��������"NOR);
		me->set("quest/wulun/time",time());
		log_file("quest/xiangfulun", sprintf("%8s(%8s) ʧ��%d�κ�ѧ�������ָ��߾���,���ִ���ȫ�ڻ��ͨ��iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"), me->query("quest/wulun/fail"),i,me->query("combat_exp")) );
		command("haha"+me->query("id"));
		return "��ϲ�������ִ󷨳ɹ���\n";
		//me->add(QUESTDIR4+"shenzhao",1);//
	}
	else
	{
		log_file("quest/xiangfulun", sprintf("%s(%s) �������ִ�ʧ��%d�Ρ�iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"),me->query("quest/wulun/fail"), i,me->query("combat_exp")) );
		tell_object(me,HIY"�����˽��ַ�����ָ�㣬���Ƕ����ִ�ת�İ���ȫȻ����Ҫ�졣\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		me->add("quest/wulun/fail",1);
		me->set("quest/wulun/time",time());
		return "�ǳ��ź��������ִ�ʧ��"+me->query("quest/wulun/fail")+"�Ρ�\n";
	}
}
// /d/xiangyang/eroad1.c

inherit ROOM;
#include <ansi.h>

void create()
{
	set("short", "�������ڽ�");
	set("long", @LONG
�����Ǿ������������ǵĶ����ڣ���ʱ���ж�����׵�ʿ��������ȥ����
�����ǿ��Խ��밲�ա����վ��ڡ��ϱ�����С�С��������������������
����������ݡ�
LONG
	);
	set("outdoors", "����");
	set("xyjob", 1);
	set("exits", ([
		"west" : __DIR__"djie2",
		"east" : __DIR__"qinglongmen",
		"north" : __DIR__"damen",
		"south" : __DIR__"ncx5",
	]));

	set("incity",1);
	setup();
}

//Jeep Title��������
/*
void init()
{
	object me = this_player();
	object party = me->query("family/family_name");
	switch (party) {
		case "������":
			if (me->query("yjj/powerup"))
			{
				me->set("title",HIR"������"NOR"��"HIC"�׽�񹦴���"NOR);
			}
			else if (me->query("wxjz/jueji"))
			{
				me->set("title",HIR"������"HIW"������ɫ��ʦ"NOR);
			}
			else if (me->query("wxjz/pass") && me->query("wxz/done"))
			{
				me->set("title",HIR"�����������ָ����"NOR);
			}
			else if (me->query("family/generation") == 35)
			{
				me->set("title","������������ɮ������ɮ");
			}
		break;
		case "������":
			if (me->query("quest/wulun/pass"))
			{
				me->set("title",HIB"������"HIC"��������"NOR);
			}
			else if (me->query("family/master_name") == "�Ħ��")
			{
				me->set("title","�������������µ���");
			}
			else if (me->query("family/master_name") == "���ַ���")
			{
				me->set("title","�����½��ַ������µ���");
			}
			else if (me->query("family/generation") == 13)
			{
				me->set("title","�����µ�ʮ��������");
			}
		break;
		case "������":
			if (me->query("emjy/pass"))
			{
				me->set("title",HIR"������"HIG"����������"NOR);
			}
			else if (me->query("emei/jianjue"))
			{
				me->set("title",HIR"�����ɻط罣������"NOR);
			}
			else if (me->query("family/master_name") == "����ʦ̫")
			{
				me->set("title", "��������������");
			}
		break;
		case "����Ľ��":
			if (me->query("shenyuan/powerup"))
			{
				me->set("title", HIY"����Ľ��"HIW"��ת���ƴ���"NOR);
			}
			else if (me->query("family/master_name") == "Ľ�ݲ�")
			{
				me->set("title", "����Ľ�ݵڶ�������");
			}
		break;
		case "��Ĺ��":
			if (me->query("quest/jiuyingm/pass"))
			{
				me->set("title", HIY"��Ĺ��"HIB"������"NOR);
			}
			else if (me->query("family/master_name") == "���" || me->query("family/master_name") == "С��Ů")
			{
				me->set("title", "��Ĺ��������´���");
			}
		break;
		case "��ɽ��":
			if (me->query("huashan/huashan") == "����")
			{
				me->delete("huashan/huashan");
				me->set("quest/huashan", "����");
			}
			if (me->query("quest/zixia/pass"))
			{
				me->set("title",HIR"��ɽ��"HIM"��ϼ������"NOR);
			}
			else if (me->query("quest/huashan") == "����")
			{
				me->set("title","��ɽ�������״�����");
			}
			else if (me->query("quest/huashan") == "����")
			{
				me->set("title","��ɽ�ɽ����״�����");
			}
		break;
		case "������":
			if (me->query("family/master_name") == "�����")
			{
				me->set("title","������ʥ�״�����");
			}
		break;
		case "����":
			if (me->query("mjqkdny/pass"))
			{
				me->set("title",HIY"����"GRN"Ǭ����Ų�ƴ���"NOR);
			}
			else if (me->query("family/master_name") == "���޼�")
			{
				me->set("title", "���̽����״�����");
			}
		break;
		case "ȫ���":
			if (me->query("quanzhen/force") && me->query("quanzhen/force") == "pass")
			{
				me->set("title",HIR"ȫ���"CYN"���칦����"NOR);
			}
			else if (me->query("family/generation") == 3)
			{
				me->set("title", "ȫ�������״�����");
			}
		break;
		case "�������":
			if (me->query("family/generation") == 6)
			{
				me->set("title",HIB"��������������״�����"NOR);
			}
			else if (me->query("family/generation") == 7)
			{
				if (me->query("family/master_name") == "������")
				{
					me->set("title", "������̹�����ʹ��������");
				}
				else
				{
					me->set("title", "������̹�����ʹ��������");
				}
			}
		break;
		case "������":
			if (me->query("family/master_name") == "�鰲ͨ")
			{
				me->set("title","�����̰���ʹ");
			}
		break;
		case "�һ���":
			if (me->query("thdjj/ronghe") && me->query("thdjj/ronghe") == "pass")
			{
				me->set("title",HIG"�һ���"HIR"��а����"NOR);
			}
			else if (me->query("family/master_name") == "��ҩʦ")
			{
				me->set("title", "�һ�������ǰ����");
			}
		break;
		case "������":
			if (me->query("yideng/ronghe") && me->query("yideng/ronghe") == "pass")
			{
				me->set("title",HIR"�����"HIY"һ��ָ����"NOR);
			}
			else if (me->query("family/master_name") == "һ�ƴ�ʦ")
			{
				me->set("title","������ϵ۴���");
			}
			if (me->query("family/master_name") == "һ�ƴ�ʦ")
			{
				me->delete("tls"); 
				me->delete("class");
			}
		break;
		case "���ư�":
			if (me->query("tiezhang/pass") && me->query("tz/piao"))
			{
				me->set("title",HIB"���ư�"MAG"����ˮ��Ư"NOR);
			}
			else if (me->query("family/master_name") == "��ǧ��")
			{
				me->set("title", "���ư��ʮ�Ĵ���������");
			}
			else if (me->query("family/master_name") == "�Ϲٽ���")
			{
				me->set("title", "���ư��Ϲٰ�������");
			}
		break;
		case "�䵱��":
			if (me->query("quest/tjq/taiji"))
			{
				me->set("title",HIR"�䵱��̫��ȭ����"NOR);
			}
		break;
		case "������":
			if (me->query("quest/hgdf/powerup"))
			{
				me->set("title",HIB"������"RED"�����󷨴���"NOR);
			}
			else if (me->query("family/master_name") == "������")
			{
				me->set("title","�����Ϲ���ǰ��ͽ");
			}
		break;
		case "ؤ��":
			if (me->query("xlz/sanzhao") && me->query("xlz/sanzhao") == "pass")
			{
				me->set("title",HIY"ؤ��"NOR"��"HIM"����ֿ��"NOR);
			}
			else if (me->query("slbw/pass"))
			{
				me->set("title",HIY"ؤ��"HIG"����ʮ���ƴ���"NOR);
			}
			else if (me->query("gb/baih7g"))
			{
				me->set("title","ؤ����߹��״�����");
			}
			else if (me->query("gb/bags") == 9)
			{
				me->set("title", "ؤ��Ŵ�����");
			}
		break;
		case "��ɽ��":
			if (me->query("family/master_name") == "������")
			{
				me->set("title","���������״�����");
			}
		break;
		default:
		break;
	}
	if (me->query("quest/shenzhao/diyun"))
	{
		me->set("title",MAG"���վ�"NOR"��"HIG"����"NOR);
	}
	if (me->query("quest/���߽���/pass"))
	{
		me->set("title",HIY"�����ɾ�"NOR"��"HIG"����"NOR);
	}
	if (me->query("oyf/hamagong") > 2)
	{
		me->set("title",HIW"����ɽׯ"NOR"��"HIG"��������"NOR);
	}
	else if (me->query("oyf/hamagong") == 2)
	{
		me->set("title",HIW"����ɽׯ"NOR"��"HIB"��󡹦����"NOR);
	}
	else if (me->query("oyf/hamagong") == 1)
	{
		me->set("title",HIW"����ɽׯ"NOR"��"MAG"ŷ��������"NOR);
	}

	if (me->query("job_time/��������ս") && (int)me->query("job_time/��������ս") > 0)
	{
		int times = (int)me->query("job_time/��������ս");
		me->delete("job_time/��������ս");
		me->add("job_time/�������ս", times);
	}
}
*/

/*
void init()
{
	object me= this_player();
	if ( me->query("oldsj")) {
		if ( !me->query("bxsj_bonus/age")) {
			if (me->query("mud_age") > 7840000)
				me->set("mud_age", 7840000);
			me->set("bxsj_bonus/age", 1);
		}
	}
	// ���� Skill ����
	if ( me->query_skill("literate", 1) > me->query("int") * 10)
		me->set_skill("literate", me->query("int") * 10);
	if ( me->query_skill("bangjue", 1) > 200)
		me->set_skill("bangjue", 200 );
	if ( me->query_skill("checking", 1) > 200)
		me->set_skill("checking", 200 );
	if ( me->query_skill("stealing", 1) > 200)
		me->set_skill("stealing", 200 );
	if ( me->query_skill("checking", 1) > 200)
		me->set_skill("checking", 200 );
	if ( me->query_skill("dagou-zhen", 1) > 200)
		me->set_skill("dagou-zhen", 200 );
	if ( me->query_skill("begging", 1) > 200)
		me->set_skill("begging", 200 );
	if ( me->query_skill("poison", 1) > 200)
		me->set_skill("poison", 200 );
	if ( me->query_skill("buddhism", 1) > 200)
		me->set_skill("buddhism", 200 );
	if ( me->query_skill("taoism", 1) > 200)
		me->set_skill("taoism", 200 );
	if ( me->query_skill("huanxi-chan", 1) > 200)
		me->set_skill("huanxi-chan", 200 );

	if (! me->query("tls")
	 && me->query_skill("liumai-shenjian", 1)){
		me->delete_skill("liumai-shenjian", 1);
		tell_object(me, HIG"�������׼ҵ���ϵͳ�Զ�ȥ�������񽣡�\n"NOR);
	}


	if ( me->query("oldsj") && me->query("bxsj_bonus/no_pk")){
		if ( time() - me->query("bxsj_bonus/no_pk") > 1296000 ){
			me->delete("no_pk");
			me->delete("bxsj_bonus/no_pk");
			tell_object(me,HIG"\n15��ʱ���ѵ���ϵͳ�Զ������������ϴ��״̬��\n"NOR);

		}
	}

}
*/
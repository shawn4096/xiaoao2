//tiezhang-xinfa.c 
inherit ITEM;

void create()
{
        set_name("�����ķ���Ҫ(��)", ({ "tiezhang xinfa", "xinfa","shu","book"}));
        set_weight(600);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "����һ�����������ķ��ؼ��ϰ벿�֣��������Ÿ�Ҫ��\n");
                set("unique", 1);
                set("treasure",1);                              
                set("value", 100000);
                set("material", "paper");
                set("skill", 
                ([
                        "name": "tiezhang-xinfa",          // name of the skill
                        "exp_required": 0,      // minimum combat experience required
                        "jing_cost":    30,     // jing cost every time study this
                        "difficulty":   30,     // the base int to learn this skill
                        "max_skill":    100      // the maximum level you can learn
                ]));
        }
}
void init()
{
        add_action("do_du", "du");
        add_action("do_du", "study");
}    
int do_du(string arg)
{
        object me = this_player();
        object where = environment(me);
        int dzlevel; 
        int neili_lost;
        if (!(arg=="tiezhang xinfa" ||arg=="book" || arg=="shu"))
        return 0;

        if (where->query("pigging")){
                write("�㻹��ר�Ĺ���ɣ�\n");
                return 1;
        }
        if (me->is_busy()) {
                write("��������æ���ء�\n");
                return 1;
        }

        if( me->is_fighting() ) {
                write("���޷���ս����ר�������ж���֪��\n");
                return 1;
        }

        if (!id(arg)) { 
                write("��Ҫ��ʲô��\n");
                return 1;
        }
		if(me->query("family/family_name") != "���ư�")
			return notify_fail("�㿴�˰��죬ʲô��˼��������\n");
        if( !me->query_skill("literate", 1) ){
                write("���Ǹ���ä����ѧ���Ļ�(literate)�ɡ�\n");
                return 1;
        }

        if( (int)me->query("jing") < 15 ) {
                write("�����ڹ���ƣ�룬�޷�ר�������ж���֪��\n");
                return 1;
        }
        
        if( (int)me->query("neili") < neili_lost) {
                write("�������������޷�������ô������书��\n");
                return 1;
        }


		if ((int)me->query_skill("tiezhang-xinfa", 1) > 100 ){
			write("�Ȿ���������˵�Ѿ�̫��ǳ�ˣ�\n");
			return 1;
			}
                neili_lost = 5;
                me->receive_damage("jing", 15,"����ԭ��");
                me->improve_skill("tiezhang-xinfa", (int)me->query_int()/3);
                write("��������ϰ�����ķ����书�ؼ����ƺ��е��ĵá�\n");
                return 1;

}

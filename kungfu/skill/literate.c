// literate.c

inherit SKILL;

string type() { return "knowledge"; }
string type3() { return "literate"; }


int valid_learn(object me)
{
	if (me->query_temp("mark/literate")) {
		me->delete_temp("mark/literate");
		return 1;
	}

	if( (me->query("family/family_name") =="������"
	|| me->query("family/family_name") =="������"
	|| me->query("family/family_name") =="������")
	&& me->query("class") == "bonze"
	&& me->query_skill("literate", 1) < 100)
		return 1;

	return notify_fail("�����ȥѧ��ѧϰ����д�֡�\n");
}
void skill_improved(object me)
{}

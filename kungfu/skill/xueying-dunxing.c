
//xueying-dunxing.c Ѫ���Ṧ
//Ѫ����
// by sohu

inherit SKILL;

string *dodge_msg = ({
"ͻȻ$n�ݵ�$N��󣬳�$N���Ӵ����ᴵ�˿�����$Nֻ���ú����쬵ģ�æ����ݳ�����ܿ���\n",
"$Nֻ����ǰ���һ����$n������һ��Ѫ����Ӱ�ݿ���$N����ʽȫ�����ڿմ���\n",
"$n���÷ɽ����Ѫ�⣬$N����ǰ��ʱ����������$n�����Σ����治֪�ĸ������ĸ��Ǽ١�\n",
"$n�੹�Ц�����һζ���˲������������࣬�ڵ���ʯ֮��㿪��$N�Ĺ�����\n",
"$Nֻ����ǰһ����$n�����λ���һ���޺��ϸ�ߣ����漴�ּ�$n�ص�ԭ�أ�ȴ�ƴ�δ�뿪��\n",
"$N�۾�һ������û��$n����Ӱ����ͷһ����$n�Ѿ�վ��$N�ĵ��Ҳ෽��վ���Ƕ����������Ц����\n",
"$n��Ȼһ�������ӷ�Ծ$Nͷ�������γ���֮�ʣ�˲���ͷ��$N���ӣ�����һ������Ц��\n",
});

int valid_enable(string usage) 
{ 
    return usage == "dodge"; 
}

int valid_learn(object me)
{
        if (me->query_skill("xuedao-jing", 1) < 20)
			return notify_fail("ѪӰ������ҪѪ������֧�ַ���ѧϰ��\n"); 
		return 1;

}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
        if( (int)me->query("jingli") < 40 )
                return notify_fail("�������̫���ˣ�������ϰѪӰ���Ρ�\n");
        me->receive_damage("jingli", 30);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"xueying-dunxing/" + action;
}
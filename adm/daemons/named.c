// yuj@sj 2001-0712
// Lklv Modify 2001-0919

string *banned_name = ({	// ��ֹ�������������κβ���
// ��ʦ������
	"ɱ��", "����", "ѩ��", "����", "ӭ��", "����",
	// snowman �������Ϊƴ�����������, laugh
	// looklove �����������Ϊ�ұȽ�ǫ�飬�ٺ�

// ϵͳ������
	"�齣", "����", "ĳЩ��", "����",
	"ĳ��", "��ʦ", "����", "�ܹ�", "����", "����", "�ſ�", "���",
	"ʬ��", "��", "��", "��", "��", "��", "���", "�Լ�", "����",
	"�й�", "�л�", "�ʵ�", "����", "ͷ­", "ɱ��", "����",

// ���˵�����
	"ë��", "��Сƽ", "������", "���ݻ�", "Ǯ���", "����", "��ҫ��",
	"��ӹ", "������", "����", "����", "³Ѹ", "��ĭ��", "ì��", "����",

// ƫ�Բ���
	"ح", "د", "ؼ", "��", "��", "��", "��", "��", "��", "��", "ڢ",
	"ڥ", "��", "��", "��", "��", "��", "ܳ", "��", "��", "��", "��",
	"��", "��", "�", "�", "��", "��", "��", "�", "��", "��", "��",
	"��", "��", "��", "��", "��", "��", "��",

// �໰�Լ���������
	"ƨ", "��", "��", "��", "��", "��", "��", "��", "��", "غ��",
	"����", "����", "ɵ��", "����", "�˸�", "����", "����", "���",
	"ͳһ", "����", "����", "����", "����", "̨��", "�ڿ�", "����",
	"����", "����", "����", "��̬", "�쵰", "�뵰", "�׳�", "����",
	"����", "����", "���", "����", "����", "����", "����", "����",
	"��", "����", "����", "����", "ռ��", "����", "����", "����",
	"�ư�", "���", "ɫ��",	"����", "����", "����", "���",

// ͨ������ �� ͨ�ó�ν
	"����", "����", "�ν�", "����", "�佫", "�ٱ�", "����", "ʿ��",
	"��ͷ", "Ѳ��", "�첶", "����", "����", "����", "����", "�ٲ�",
	"̫��", "����", "�¹�", "��Ů", "��Ů", "���", "����", "���",

	"����", "ǿ��", "���", "�ٷ�", "���", "���", "��ͽ", "��å",

	"����", "С��", "����", "�", "��ؤ", "����", "��ͷ", "���˺�",
	"�ŷ�", "����", "����", "����", "�η�", "���", "���", "����",
	"ׯ��", "�ܼ�", "���", "����", "�ҹ�", "�ϰ�", "�ƹ�", "����",
	"����", "����", "����", "�÷�", "ũ��", "ҽ��", "ҩʦ", "��ҩ��",

	"����", "����", "����", "����", "�ο�", "�Ŀ�", "�̿�", "�ÿ�",
	"ȭʦ", "��ʦ", "��ʦ", "����", "����", "��Ժ", "��ͷ", "������",
	"����", "��ʿ",

	"��ү", "����", "��ү", "����", "�๫", "����", "С��", "̫̫",
	"Ѿ��", "�Ҷ�", "����", "����", "Сͯ", "����", "����", "ʹŮ",

	"ү", "��", "��", "ĸ", "��", "��", "��", "��", "��", "��",
	"����", "����", "�ɷ�",	"�Ϲ�", "����", "�ͷ",
	"Ů��", "Ů��", "Ů��", "Ů��", "����", "����", "Ѿͷ", "С��",
	"����", "����", "�е�", "�к�", "����", "С��", "С��", "��ͯ",
	"����", "��ͷ", "����", "����", "����", "����", "׳��", "����",

	"����", "���", "����", "��ʿ", "ɳ��", "����", "ɮ��", "����",
	"��ʦ", "ʦ̫", "����", "�޺�", "��ʦ", "����", "����", "����",
	"ʦ��", "ʦ��", "ʦ��", "ʦ��", "ʦ��", "ʦ��", "ʦ��", "����",

	"����", "կ��", "����", "����", "����", "����", "����", "����",
	"̳��", "����", "����", "����", "����", "��ͷ", "����", "���",
	"����", "����", "��ͽ",
});

string *novel_name = ({		// ��ֹ��������ȫƥ��
// ����������
	"����", "а��", "�ٸ�", "����", "���ֺú�", "�ú�", "Ӣ��", "ΰ��",
	"�����", "��ػ�",
// ��ϵͳ������
	"�ж�˹̩", "��������", "�Ͷ�����",
	"����", "����", "ׯ��", "�Ƶ�", "����", "��ʼ��", "����", "����",
	"�ܲ�", "����", "��Ȩ", "����", "���", "���Ƴ�", "�ĺ��", "½ѷ",
	"����", "����", "��Τ", "����", "����", "�ŷ�", "����", "�˰�",

	"���", "�Ÿ�", "����", "����", "���", "����", "����Ԫ", "ŷ����",
	"½��", "��ά", "����", "����", "˾������",

	"Ҷ���", "����ΰ", "֣����", "Ī��ε", "����", "��ѧ��", "����",
	"�޴���", "���»�", "����", "�Ա�ɽ", "�ƺ�",

	"����ɽ", "����", "����ʯ", "�ֱ�", "����", "���", "��ˮ��", "��ǻ�",
	"���ݻ�", "����", "������", "����", "����", "���»�", "Ҷ��Ӣ", "ë��Ӣ",
	"�����", "�¶���", "ҶȺ", "�޸�",
	"����", "˹����", "����˼", "����˹",

	"������", "����", "�ž�", "���", "�ؼ�", "�����", "����",

// Mud ���������ɡ�������
	"����", "�置",	"����", "��ԭ", "�Ͻ�", "����", "�ƺ�",
	"��ɽ", "��ɽ", "��ɽ", "��ɽ", "̩ɽ", "ѩɽ", "��ɽ", "��ɽ",
	"����ɽ", "����ɽ", "����ɽ", "�䵱ɽ", "����ɽ", "����ɽ",
	"����", "�һ���", "���ߵ�", "������", "���͵�", "��ľ��",
	"����", "�䵱", "ؤ��", "����", "Ľ��", "��Ĺ",	"ȫ��",
	"����", "����", "�һ�", "����", "����", "����", "����",
	"������", "������", "������", "������", "�����", "������",
	"�������", "����", "������", "�嶾��", "ȫ���", "������",
	"������", "�䵱��", "ȫ����", "������", "��Ĺ��", "������", "������",
	"��ɽ��", "��ɽ��", "��ɽ��", "��ɽ��", "̩ɽ��", "��������",
	"���ư�", "��ũ��", "���°�", "�ƺӰ�", "����Ľ��",

// ��ͨ���� �� �Ѷ�׫NPC����
	"���ִ���", "��ͨ����", "����", "�����ļ�", "���޳�", "���޳�",
	"��������", "�Ծ�ү", "���ǿ�", "�����", "����ͨ",
	"Ǯ��", "Ǯ�ۿ�", "������", "������", "����ˮ", "�販ʿ", "˵����",
	"�в�ɮ", "�����", "������", "�տն�", "��ϼ��", "�����", "Ǯ����",

// ����
	"��ȸ", "����", "����", "��ͷ��", "֧��Ѽ", "������",
	"����", "����", "����",	"����", "�˻���", "�۾���", "����", "֩��",
	"���", "Ы��", "��Ӭ", "���", "���", "����", "����", "����",
	"��", "����", "���", "����", "�ڻ�", "���", "����",
	"�ϻ�", "ʨ��", "����", "����", "����", "����", "ͷ��", "�����",
	"Ұ��", "Ұ��", "Ұ��", "ҰѼ", "Ұ��", "Ұ��", "����", "����",
	"��ţ", "�ǹ�", "¿��", "ˮţ", "�׶�", "Ѽ��", "�ƹ�",
	"����", "����",
	"�ڹ�", "����", "����", "����", "����", "����", "�з", "����",
	"����", "����", "��Ҷ��",

// ��ӹԭ��С˵����
	// A
	"����", "����",
	"������", "���ᶽ", "������", "������", "������", "��С��",
	"���ó�", "������", "������", "����", "����", "����", "����", "����",
	"����", "����", "����", "����", "����", "����", "����", "��ʤ", "����",

	// B
	"��̩", "����ʯ", "������", "���շ�ʦ",
	"������", "����", "�׹���", "����", "������", "�׺���", "�׺���",
	"�װ���", "������", "�׶�", "����",
	"������", "����ʯ", "������",
	"����", "����", "����", "����",
	"����ͬ", "������", "����Ҷ", "��ϧ��",
	"��ǧ��", "�����", "������",
	"����", "����",
	"��̩", "��ԫ", "����",
	"������", "������", "����̨", "������", "����", "�����", "����ʽ",
	"�ٲ���", "�˵�",

	// C
	"����", "�ٰٳ�",
	"�¼���", "������", "�½���", "������", "�´ﺣ", "������", "����",
	"�¹���", "��ԲԲ", "�¸߲�", "������", "�´�", "����ؤ", "����",
	"�³�֮", "������", "����",
	"��Ӣ", "������", "�̳���", "����˪", "����˪", "������", "��ά��",
	"����", "������",
	"����", "�ɲ���", "����ѧ", "�ɸ�", "�ɼ�˼��", "���",
	"����־", "����־", "����֮", "������", "������", "������",
	"��ϣ��", "��־��", "�ް�Ȫ", "�ް�ʤ", "���̻�", "��Ϲ��", "����ɽ",
	"���ӷ�", "����", "����", "�̵���",
	"������", "����", "����", "��˾��", "�ܻ���",
	"���̨", "�����",
	"�ι�", "��ͨ", "�ι�", "����", "��ʶ",
	"������", "�ɻ���", "������", "����", "�Բ���", "�̽�", "���˹",
	"������", "������", "����",

	// D
	"����", "����",
	"�Űٵ�", "��ϣ��", "������",
	"������", "������", "����", "����", "����", "����ȫ", "����",
	"������", "������", "����", "����", "��ͬ", "������",
	"�˰ٴ�", "�˱���", "�˰˹�", "����",
	"������", "������", "������", "����", "�����", "������",
	"��¡", "�����",
	"���", "���", "���", "��", "��ͷ��",
	"�ɶ�", "�ɽ�", "����", "����", "����", "����",
	"��Ħ", "�����", "�²�", "�¶�", "�³�",
	"�������", "���˿", "������", "���׷�", "������", "����", "����ɽ",
	"��������", "��ľԪ", "��ʷ", "�Կ���", "������", "�������", "�����",

	// E
	"������",

	// F
	"������", "��ң", "����", "����", "����", "���ж�", "��һ��",
	"���ĳ�",
	"�����", "����", "����", "��֤", "������", "���е�", "������",
	"������", "����", "����",
	"������", "�粻ƽ", "������", "�粨��", "����", "�����",
	"������", "��һ��", "����",
	"�밢��", "������", "��Ĭ��", "���", "������", "��֪ͬ", "���",
	"���ѵ�", "�벻��", "�벻��", "��̹",
	"�ѱ�", "��Ҫ����",
	"����", "��һ��",
	"�ⲻƽ", "�⹭Ӱ", "������",
	"��˼��", "������", "������", "������", "����",

	// G
	"��Х��", "����", "����", "��ܽ", "����²", "������",
	"�߸���", "��ɽ��", "�����", "����̩", "�����", "���ճ�", "�߿���",
	"������", "��������",
	"������", "�����", "����",
	"����ֹ", "��������", "��ұǬ",
	"���Ƴ�", "������", "������",
	"�ذ���", "�ط���", "����÷",
	"������", "����˪",
	"�����", "�����", "��ͨ",
	"������", "�˽��",
	"����ȭ", "����֮",
	"��һ��", "���˴�",
	"�����", "�º���", "����", "�ʱ���", "�ɹ��", "��ͷ��", "����", "���ż�",

	// H
	"�ڰ���", "����",
	"�����", "����̨",
	"�����", "��̫��", "������", "������", "�κ�ҩ", "�����", "��˼��",
	"������", "������",
	"���ﲼ", "�ͫ|", "�Ͷ���",
	"������", "��СӨ", "���ĳ�", "������", "���޹�", "����ؤ", "��ǧҶ",
	"���ֶ�",
	"���", "��һ��", "����ţ", "����֮", "���µ�", "�����", "������",
	"������", "������",
	"������", "������",
	"������", "���״�", "���׶���", "��������", "�����Ļ�", "������",
	"����", "��ҩʦ", "����", "�Ʋ���", "���ӹ�", "��ϣ��", "�ƹ���",
	"�Ƹ�", "�ƽ��", "��ü", "������", "����", "�ƶ�ë��", "������",
	"����", "����ͩ", "��Ԫ��", "������",
	"���߹�", "���貨", "�鰲ͨ", "������", "������", "�鳯", "��ʤ��",
	"����Ӣ", "�����", "��ͨ��", "�����",
	"������", "����Ӱ", "������", "����",
	"����", "������",
	"�´�ͨ", "����",
	"������", "����", "����", "����˹��",
	"�۷�", "�۹�", "�۾�", "����", "��Ҷ", "������", "����ʹ", "��̫��",
	"�մ�ͨ", "��������", "�ױ���", "����Ħ", "�ʸ���", "��������", "������",

	// J
	"������", "������",
	"��ȫ��", "���ַ���", "������",
	"���ĸ�", "����", "������", "������", "��ʿ��",
	"����ܽ", "������", "����ʩ",
	"��С��", "����ɽ", "��ʦ��", "����",
	"������", "�ֲ�", "���˴�",
	"����̩", "����ʢ",
	"����", "�ս�", "�շ�",
	"������", "��ľ", "������", "�����",
	"���", "����ʤ", "����", "��������", "����ͨ",
	"����", "����", "����", "����", "����", "����",
	"��Զ", "����", "����", "����", "����", "����", "�Ħ��", "����", "������",

	// K
	"����", "������",
	"�����", "�����",
	"�ռ�", "����", "����", "����", "���Ĳ�",
	"������", "������",
	"������", "��˿��", "����", "��ľ",

	// L
	"������", "����", "��Ī��", "����ˮ", "������", "������", "�����",
	"����ɽ", "����", "��־��", "����ԫ", "���Գ�", "�����", "���",
	"��͢��", "��Ƽ", "������", "��ʽ��", "������", "���Ԫ", "���Ĵ�",
	"�����", "����",
	"��Զͼ", "������", "��ƽ֮", "������", "�ֳ�Ӣ", "������", "������",
	"������", "����", "���Խ�",
	"������", "������", "������", "����ׯ", "������", "��֮��", "��Ԫ��",
	"���˷�", "������", "��һ��", "������", "������", "�����", "��ݼ",
	"����", "����",
	"���ĵ�", "������", "������", "��С��", "������", "������", "����ƽ",
	"����",
	"½����", "½����", "½��ͨ", "½�˷�", "½չԪ", "½����", "½��",
	"½��˫", "½����", "½��Ӣ", "½����", "½����", "½��",
	"����˼", "��˪��",
	"�����", "�����", "����", "����",
	"³�н�", "³��", "³����",
	"¹����", "¹�ȿ�",
	"�����", "����",
	"�ϲ���", "��ͷ��",
	"����", "���˽�", "�޴�ǧ", "������",
	"����", "��һХ",
	"�����", "���", "����", "����", "������", "��������", "������",
	"������", "���", "��ǫ", "�͵�ŵ", "¬һ��", "������", "������",
	"����ʹ", "������", "����",

	// M
	"������", "����", "����Ϊ", "����ͨ", "���ҿ�", "���ƾ�", "����",
	"������", "����", "����Ԫ", "���п�", "������", "�����", "����",
	"������", "����", "������", "������", "����ͦ", "������", "����",
	"Ī����", "Ī��", "Ī������",
	"���˷�", "������",
	"÷����", "÷����", "÷����", "÷����", "÷��", "÷��ܰ", "÷����",
	"Ľ�ݲ�", "Ľ�ݸ�", "Ľ�ݾ���", "Ľ����",
	"ľ����", "ľ׿��", "ľ�Ĳ�", "ľ����", "ľ�߷�", "ľ����", "ľɣ",
	"�彣��", "�彣��",
	"�¹���", "�����", "������",
	"�Ͻ���", "��ʦ��", "������", "�ϲ���", "����", "���",
	"��Ϊ��", "��˼��", "�׺�Ұ",
	"���ӻ�", "����",
	"���", "ë����", "éʮ��", "����", "����", "���׶�", "�ɸ�",
	"��", "���ʹ", "�ι�", "Ħڭ��˼",
});

//	MudOS ���� >= 979 ������ʱ�ݹ���� YUJ@SJ 2001-12-28

string *novel_name1 = ({
	// N
	"��ϣ��", "�ϻ���", "����ͨ", "����", "�Ϻ�����",
	"�߲���", "�߲�С", "�ߺ�",
	"������", "������", "Ŭ����", "����", "��Ħ��",
	// O
	"ŷ����", "ŷ����", "ŷ������", "ŷ����֮",

	// P
	"ƽһָ", "ƽ����", "ƽ����", "ƽ����", "ƽ��", "ƽ��",
	"���о�", "��Ө��", "������", "������",
	"��ͷ��", "Ƥ����", "�����", "�����",

	// Q
	"�ݳ���", "�ݷ�",
	"������", "�벮��", "��Ԫ��", "����ŵ��", "����", "���ư�",
	"�����", "������", "��־��", "�����",
	"������", "�Ƿ�", "�Ǹ�",
	"��ǧ��", "��ǧ��", "��ǧ��",
	"�����", "������", "����", "����",
	"�غ���", "����֮", "�ؽ�", "�ؾ�", "��ΰ��", "������", "�ض�",
	"Ǯ�ϱ�", "Ǯ�ཡ", "Ǯ����", "Ǯ����", "Ǯͨ��",
	"ȫ����", "ȫ��",
	"Ǭ¡", "�𴦻�", "��ɽ��", "�ٶ�", "����", "������", "�续", "Ȫ����",
	"������", "���", "����",
	// R
	"������", "��ӯӯ", "�η���", "��ͨ��",
	"������", "��ʿ��",
	"������", "�����", "��", "��",
	"���Ӿ�", "�ٲ�", "���", "�˳���", "���", "������",

	// S
	"ʩ����", "ʩ����", "ʩ��",
	"˾ͽ��", "˾ͽ��", "˾ͽ��", "˾ͽ����", "˾ͽǧ��",
	"˾����", "˾����", "˾����",
	"ʯ��", "ʯ����", "ʯ����", "ʯ˫Ӣ", "ʯɩ", "ʯ��¶", "ʯ����", "ʯ��",
	"ʷ����", "ʷ����", "ʷ�Ͻ�", "ʷ���", "ʷ��ǿ", "ʷС��", "ʷ�ڵ�",
	"ʷ�ٿ�", "ʷ��ɽ", "ʷ�Ǵ�", "ʷ����", "ʷ����", "ʷ��ʯ", "ʷ��",
	"ʷ����", "ʷ����",
	"ɳͨ��", "ɳ�콭", "ɳ�ϴ�", "ɳ����",
	"����", "���Ǻ�", "�����", "��³��", "����", "��ϰ֮", "�շ���",
	"�ո�", "������",
	"�滯��", "����",
	"��Զ��", "������", "������", "���챣", "�ε·�", "����", "���ײ�",
	"�ﲻ��", "���پ�", "���ͨ", "��շ�", "�����", "���", "��˼��",
	"�����", "������", "������", "������", "������", "������",
	"����", "�ۺ�",
	"����̫", "�̱���",
	"����ɽ", "����ɽ", "����ɽ", "����ɽ", "��Сɽ", "����", "������",
	"ɣ����", "ɣ˹��", "ɣ�ɺ�", "ɣ����", "ɣ��", "ɣ��", "ɣ����",
	"�Ϲ���", "�Ϲٺ�", "�Ϲٽ���", "�Ϲ���ɽ", "�Ϲ�", "�Ϲ�����",
	"ˮ��", "ˮ��", "ˮ�", "ˮ��", "ˮ��",
	"��־��", "���˿�",
	"���", "���Ǳ", "�����",
	"˫��", "˵����", "��ˮ����", "����", "����", "����ͼ", "��ͷ��", "����",
	"ɵ��", "����ɽ", "ʨ����", "ʱ����", "��ɽ", "����", "��Ƥ��", "ɥ�Ź�",
	// T
	"̷��", "̷��", "̷����", "̷��", "̷����", "����ة", "̷����",
	"���ũ", "�ﲮ��", "������", "�����",
	"������", "����", "����", "���", "����", "�쾵", "���", "��ɽͯ��",
	"����ɮ", "����", "����",
	"������", "�ƹ���", "����", "����ү",
	"ͯ����", "ͯ����", "ͯ�׺�", "ͯ��", "١����",
	"���Ӱ�", "�հ���", "�պ�Ӣ", "�վ�",
	"�Ҹ���", "�Ҹ���", "�һ���", "��ʵ��", "��Ҷ��", "��֦��", "�Һ�",
	"����", "�����", "������", "����",
	"����", "��ľ��", "ͺ����", "ͼ����", "ͼ������", "��һ��", "��ծ��", "̫����",

	// W
	"������", "����һ", "������", "���ѹ�", "������", "��ʮ��", "��̶",
	"����Ӣ", "������", "����Ƽ", "����ͨ", "������", "��־̹", "����",
	"������", "���Ҿ�", "���ҿ�", "��Ԫ��", "����ǿ", "��ά��", "����",
	"��Ω��", "������", "������", "����˥", "������", "����", "����",
	"������", "������", "����ͨ", "������", "��Х��",
	"������", "�·���", "�·�ɽ", "�·���", "�·�ʩ", "�·���", "����",
	"������", "���з�", "���е�", "���ʺ�", "����", "����",
	"�����", "���ʤ", "�ⳤ��", "������", "������", "��Ӧ��", "�⿲",
	"��֮��", "�����", "������", "������", "�ⱦ��", "���Ӣ", "����",
	"�����", "���ͨ", "�����", "�⾢��", "����", "��ƽ",
	"������", "������", "�޳�", "��ɫ", "����", "�޳���",
	"��ặ�", "����ͨ", "�����", "������", "������", "������", "����Ӥ",
	"�����", "����", "����",
	"������", "��̩��",
	"�����", "�Ų���",
	"ΤС��", "ΤһЦ", "Τ����",
	"������", "���", "������", "������", "������",
	"����ɽ", "���", "���ƽ", "������", "�����",
	"����Ƽ", "���պ���", "���պ���", "���հ��Ǵ�",
	"����̨", "�߶�����", "���ϴ�",	"��������", "���", "���",

	// X
	"���Ź�ֹ", "������",
	"����", "���л�", "�����", "��Զɽ",
	"Ѧȵ", "ѦĽ��", "Ѧ��Զ", "Ѧ��",
	"С��Ů", "С��", "С��", "С��", "С����", "С����", "С��",
	"С��ͷ", "С��", "С��", "С��",
	"л�̿�", "лѷ", "л����",
	"���", "���ı�",
	"��ѩ��", "������", "��ѩ��", "�Ĺ���", "����",
	"�����", "�쳱��", "���", "���", "��С��", "���촨",
	"��ѩͤ", "��׿��",
	"��˫��", "��Ȼ", "������", "����", "��Ϫ",
	"������", "�����",
	"����", "��ʹ", "����", "����", "����", "����", "����", "����", "����",
	"������", "��ң��", "Ѫ����", "Ѫ������", "����ͨ", "����", "����",
	"����", "��Ԫ��", "�г�", "�е�",

	// Y
	"���", "�", "������", "���Э", "����ͤ", "���", "���",
	"����", "���",	"����֮", "�ͤ", "������", "���л�",
	"�ξ�", "����", "��̹֮", "��Ѹ",
	"����ͤ", "������", "��Ұ��", "������", "����", "������", "��", "���",
	"����»", "���޸�", "������",
	"Ԭ���", "Ԭ��־", "Ԭ����", "Ԭ����", "Ԭʿ��", "Ԭö",
	"Ԫ��", "Ԫʹ", "Ԫ��", "Ԫ�巽", "Ԫ��", "Ԫ�㲨",
	"����Ⱥ", "����ɺ", "������", "����", "����",
	"��׺�", "������", "����ͬ", "�����", "��ɩ", "������", "������",
	"���˺�", "����ͤ", "�ڹ��", "�ڰ�", "��ɩ",
	"������", "�����", "�ᳯ��",
	"������", "������", "������", "������", "������", "������", "����",
	"������", "������", "����", "�����",
	"�״��", "������", "�׼�", "�׹���",
	"��־ƽ", "������", "������",
	"Ҧ����", "Ҧ��", "Ҧ�ش�", "Ҧ��Ȫ",
	"���к�", "�Ƶ���", "����÷", "�ƺ�",
	"Ҷ����", "Ҷ����",
	"Ү����", "Ү�ɺ��", "Ү��Ī��", "Ү����³��", "Ү����Ԫ", "Ү�ɳ���",
	"Ү�ɽ�", "Ү����",
	"Ӣ����", "Ӣ�", "����",
	"Ե��", "Բ��", "Բ��", "Բҵ", "Բ��",
	"����", "����", "�Ǻ�", "����", "����", "�ǹ�", "�Ǿ�", "����", "����",
	"�Բ�Ǭ", "�Դ�ƽ",
	"������", "������", "�ֻ�",
	"�պ�", "��ԫ", "������", "������", "����", "Ӧ��",
	"Ӻ��", "һ��", "�ֺ�", "�Ĳ�", "������", "�ȵ�ʤ", "ξ����", "��Ҷ����",

	// Z
	"������", "�ž���", "�Ŵ�ɽ", "����Ϫ", "����", "���޼�", "�Ű���",
	"�ų˷�", "�ų���", "�����", "��ȫ��", "����", "�ź���", "�ŷ���",
	"��ʮ��", "�ŵ���", "�ſ���", "�Ž���", "�ž�", "�Ű���", "��־��",
	"������", "��һå", "�Ŷ���", "�ų���", "����", "�Ŵ���", "������",
	"����", "�ſ�",
	"������", "�½�",
	"�ܲ�ͨ", "������", "������", "�ܵ�", "���", "����Ӣ", "��¡",
	"������", "������", "�ܹ�ͩ", "��ͩ", "����", "������", "�ܰ���",
	"��Ӣ��", "������", "����",
	"׿����", "׿����",
	"������", "��ȫ", "������",
	"����", "������", "���", "��Բ", "�Һ�", "������", "����",
	"�Һ��",
	"�쵤��", "������", "������", "�����", "�쳤��", "���", "��Ԫ�",
	"�찲��",
	"�����", "��ǧ��",
	"����Ÿ", "����ţ", "����", "��ͼ��",
	"֣����", "֣�ɹ�", "֣��ˬ", "֣��", "֣����", "֣��֥", "֣����",
	"֣����",
	"�԰�ɽ", "����", "��־��", "��Ǯ��", "�Գ�֮", "���", "�Ժ�",
	"������", "������", "��һ��",
	"ׯ�й�", "ׯ�", "ׯ͢��", "ׯ�ʳ�",
	"��ά��", "����", "��������",
	"������", "����Ӣ", "������", "����ɩ", "��С��", "�����", "����",
	"�Ӱ���", "��־��", "����",
	"�ǹ�", "ժ����", "ղ��", "ֹ��", "�����", "��ɽ��", "�Ӵ�", "����",
	"�ܱ�", "������", "������", "��ľ��", "���", "�׻�", "��", "չ��",
});

int valid_name(string name)
{
	int len = strlen(name);
	int i, j;

	if (member_array(name, novel_name) != -1)
		return 0;
	if (member_array(name, novel_name1) != -1)
		return 0;
	for (i = 0; i < len; i += 2)
		for (j = i + 1; j < len; j += 2)
			if (member_array(name[i..j], banned_name) != -1)
				return 0;
	return 1;
}
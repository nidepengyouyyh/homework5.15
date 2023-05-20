#ifndef STRUCT_ENTRY
#define STRUCT_ENTRY
 
//������
template<typename K, typename V> struct entry
{
	K key;      //�ؼ���
	V value;    //������
 
	//���캯��
	entry(K k = K(), V v = V()) :key(k), value(v) {}   
	entry(const entry<K, V>& e) :key(e.key), value(value) {}
	bool operator<(const entry<K, V>& e);
	bool operator>(const entry<K, V>& e);
	bool operator==(const entry<K, V>& e);
	bool operator!=(const entry<K, V>& e);
};
 
template<typename K, typename V> bool entry<K,V>::operator<(const entry<K, V>& e)
{
	return this->key < e.key;
}
 
template<typename K, typename V> bool entry<K, V>::operator>(const entry<K, V>& e)
{
	return this->key > e.key;
}
 
template<typename K, typename V> bool entry<K, V>::operator==(const entry<K, V>& e)
{
	return this->key == e.key;
}
 
template<typename K, typename V> bool entry<K, V>::operator!=(const entry<K, V>& e)
{
	return this->key != e.key;
}
#endif

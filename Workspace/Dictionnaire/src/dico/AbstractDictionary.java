package dico;

public abstract class AbstractDictionary implements IDictionary
{
	public int taille;
	public Object[] key;
	public Object[] value;
	private int numberelement;
	abstract int indexOf(Object key);
	abstract int newIndexOf(Object key);
	int size()
	{
		return numberelement;
	};
	
	@Override
	public Object get(Object p_key)
	{
		/*return the value of the key which is in the array
		 */
		int index=this.indexOf(p_key);
		if (index==-1)
		{
			return "Valeur de "+p_key+" introuvable.";
		}
		else
		{
			return /*"Définition de "+p_key+": "+*/this.value[index];
		}
	}
	
	@Override
	public void put(Object key,Object value)
	{
		/*record a new couple key-value
		 */
		if (this.newIndexOf(key)!=-1)
		{
			this.numberelement++;
			int index=this.newIndexOf(key);
			this.key[index]=key;
			this.value[index]=value;
			System.out.println("L'ajout a réussi");
			//we pack the value and the key at the same index 
		}
		else
		{
			System.out.println("Clé déjà prise");
		}
	}
	
	@Override
	public boolean isEmpty()
	{
		/*return true if it is empty
		 * else return false
		 */
		return this.size()==0;
	}
	
	@Override
	public boolean containsKey(Object key)
	{
		/*return true if the key is known 
		 * else return false
		 */
		int index=this.indexOf(key);
		return index != -1;
	}
}

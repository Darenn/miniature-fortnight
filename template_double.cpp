template <class T, void (*delete_T)(T &)>
template <char const *const open_sons, char const *const sep_brothers,
          char const *const close_sons>
std::ostream &Tree<T, delete_T>::out_put(std::ostream &ost) {}

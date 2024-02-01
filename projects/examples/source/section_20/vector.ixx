module;

#include <concepts>
#include <iterator>
#include <memory>

export module vector;

namespace estd
{
    template < typename C > class const_iterator
    {
    public:

        using  concept_tag =    contiguous_iterator_tag;
        using category_tag = random_access_iterator_tag;

        using  obj_t = typename C:: obj_t;
        using  ptr_t = typename C:: ptr_t;
        using  ref_t = typename C:: ref_t;
        using  dif_t = typename C:: dif_t;

        using cptr_t = typename C::cptr_t;
        using cref_t = typename C::cref_t;

        constexpr const_iterator()          noexcept : m_ptr()    {}
        constexpr const_iterator(ptr_t ptr) noexcept : m_ptr(ptr) {}

        [[nodiscard]] constexpr ref_t operator* () const noexcept { return *m_ptr; }
        [[nodiscard]] constexpr ptr_t operator->() const noexcept { return  m_ptr; }

        constexpr const_iterator & operator++() noexcept { ++m_ptr; return *this; }
        constexpr const_iterator & operator--() noexcept { --m_ptr; return *this; }

        constexpr const_iterator operator++(int) noexcept 
        {
            const_iterator tmp = *this;
            ++*this;
            return tmp;
        }

        

        constexpr const_iterator operator--(int) noexcept {
            const_iterator tmp = *this;
            --*this;
            return tmp;
        }

        constexpr const_iterator& operator+=(const difference_type _Off) noexcept {
            _Verify_offset(_Off);
            m_ptr += _Off;
            return *this;
        }

        [[nodiscard]] constexpr const_iterator operator+(const difference_type _Off) const noexcept {
            const_iterator tmp = *this;
            tmp += _Off;
            return tmp;
        }

        [[nodiscard]]_FRIEND constexpr const_iterator operator+(
            const difference_type _Off, const_iterator _Next) noexcept {
            _Next += _Off;
            return _Next;
        }

        constexpr const_iterator& operator-=(const difference_type _Off) noexcept {
            return *this += -_Off;
        }

        [[nodiscard]] constexpr const_iterator operator-(const difference_type _Off) const noexcept {
            const_iterator tmp = *this;
            tmp -= _Off;
            return tmp;
        }

        [[nodiscard]] constexpr difference_type operator-(const const_iterator& _Right) const noexcept {
            _Compat(_Right);
            return m_ptr - _Right.m_ptr;
        }

        [[nodiscard]] constexpr reference operator[](const difference_type _Off) const noexcept {
            return *(*this + _Off);
        }

        [[nodiscard]] constexpr bool operator==(const const_iterator& _Right) const noexcept {
            _Compat(_Right);
            return m_ptr == _Right.m_ptr;
        }

        [[nodiscard]] constexpr strong_ordering operator<=>(const const_iterator& _Right) const noexcept {
            _Compat(_Right);
            return _Unfancy(m_ptr) <=> _Unfancy(_Right.m_ptr);
        }

        [[nodiscard]] constexpr const value_type* _Unwrapped() const noexcept {
            return _Unfancy(m_ptr);
        }

        constexpr void _Seek_to(const value_type* _It) noexcept {
            m_ptr = _Refancy<_Tptr>(const_cast<value_type*>(_It));
        }

    private:

        _Tptr m_ptr; // pointer to element in vector

    }; // template < typename C > class const_iterator

    template <class _Myvec>
    struct pointer_traits<_Vector_const_iterator<_Myvec>> {
        using pointer = _Vector_const_iterator<_Myvec>;
        using element_type = const typename pointer::value_type;
        using difference_type = typename pointer::difference_type;

        _NODISCARD static constexpr element_type* to_address(const pointer _Iter) noexcept {

            return _STD to_address(_Iter._Ptr);
        }
    };

} // namespace estd
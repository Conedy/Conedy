" Vim syntax file
" Language:	neurosim
" Maintainer:	You!
" Last Change:	05.02.2010
" 
" copy/link to this file to  /usr/share/vim/vimcurrent/syntax (debian) and 
" then set filetype=neurosim  
"
" Quit when a (custom) syntax file was already loaded
if exists("b:current_syntax")
  finish
endif

syn keyword	controlKeywords     for while if vectorFor loop
syn keyword     nsTypes             network int double node


syn match       nsComment           "#.*$"

syn region nsString start='"' end='"' contained
syn region nsDesc start='"' end='"'

hi def link controlKeywords Statement
hi def link nsTypes         Type
hi def link nsComment       Comment
hi def link nsString        Constant
hi def link nsDesc          String

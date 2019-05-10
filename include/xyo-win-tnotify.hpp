//
// XYO Win Library
//
// Copyright (c) 2018-2019 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_WIN_TNOTIFY_HPP
#define XYO_WIN_TNOTIFY_HPP

#ifndef XYO_WIN_INOTIFY_HPP
#include "xyo-win-inotify.hpp"
#endif

namespace XYO
{
	namespace Win
	{

		using namespace XYO;
		using namespace XYO::Core;

		template<typename Class, typename Function, typename Data> class TNotify :
			public virtual Object,
			public virtual INotify
		{
				XYO_CORE_DISALLOW_COPY_ASSIGN_MOVE(TNotify);
			protected:
				TPointer<Class> object;
				Data data;
				Function function;
			public:
				inline TNotify() {};
				inline ~TNotify() {};

				inline void set(TPointer<Class> object_, Function function_, Data data_)
				{
					object = object_;
					function = function_;
					data = data_;
				};

				void notify();

				inline void clear()
				{
					object.memoryDelete();
				};
		};

		template<typename Class, typename Function, typename Data>
		void TNotify<Class, Function, Data>::notify()
		{
			return (*object.*function)(data);
		};

	};
};

#endif


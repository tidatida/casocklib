/*
 * casocklib - An asynchronous communication library for C++
 * ---------------------------------------------------------
 * Copyright (C) 2010 Leandro Costa
 *
 * This file is part of casocklib.
 *
 * casocklib is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * casocklib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with casocklib. If not, see <http://www.gnu.org/licenses/>.
 */

/*!
 * \file casock/rpc/asio/protobuf/base/RPCCommunicator.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__CASOCK_RPC_ASIO_PROTOBUF_BASE__RPC_COMMUNICATOR_H_
#define __CASOCKLIB__CASOCK_RPC_ASIO_PROTOBUF_BASE__RPC_COMMUNICATOR_H_

#include <sstream>

#include "casock/proactor/asio/base/Communicator.h"

namespace google {
  namespace protobuf {
    class Message;
  }
}

namespace casock {
  namespace proactor {
    namespace asio {
      namespace base {
        class SocketChannel;
      }
    }
  }

  namespace rpc {
    namespace protobuf {
      namespace api {
        class RpcResponse;
      }
    }

    namespace asio {
      namespace protobuf {
        namespace base {
          using casock::proactor::asio::base::SocketChannel;

          class RPCCommunicator : public casock::proactor::asio::base::Communicator
          {
            public:
              explicit RPCCommunicator (SocketChannel* const pChannel);

            private:
              virtual ::google::protobuf::Message* createRecvMessage () = 0;

            protected:
              void onSentSize (const ::asio::error_code& error, const std::stringstream* buffer, ::boost::function<void(const ::asio::error_code&)> handler);
              //void onSentSize (const ::asio::error_code& error, const std::stringstream* buffer, ::boost::function<void()> handler);
              void onSentBuffer (const ::asio::error_code& error, const std::stringstream* buffer, ::boost::function<void(const ::asio::error_code&)> handler);
              //void onSentBuffer (const ::asio::error_code& error, const std::stringstream* buffer, ::boost::function<void()> handler);

              void onReadSize (const ::asio::error_code& error, ::boost::function<void(const ::asio::error_code&, google::protobuf::Message*)> handler);
              void onReadBuffer (const ::asio::error_code& error, char* buffer, ::boost::function<void(const ::asio::error_code&, google::protobuf::Message*)> handler);

              void sendMessage (const ::google::protobuf::Message* const message, ::boost::function<void(const ::asio::error_code&)> handler);
              //void sendMessage (const ::google::protobuf::Message* const message, ::boost::function<void()> handler);
              void recvMessage (::boost::function<void(const ::asio::error_code&, ::google::protobuf::Message*)> handler);

            private:
              int mSize; /*!< should be a size_t, but ::google::protobuf::Message::ByteSize () returns an int */
          };
        }
      }
    }
  }
}

#endif // __CASOCKLIB__CASOCK_RPC_ASIO_PROTOBUF_BASE__RPC_COMMUNICATOR_H_

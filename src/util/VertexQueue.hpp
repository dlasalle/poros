/**
* @file VertexQueue.hpp
* @brief The Vertex queue class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-10-15
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to
* deal in the Software without restriction, including without limitation the
* rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
* DEALINGS IN THE SOFTWARE.
*/

#ifndef POROS_SRC_VERTEXQUEUE_HPP
#define POROS_SRC_VERTEXQUEUE_HPP

#include "solidutils/FixedPriorityQueue.hpp"


namespace poros
{


class VertexQueue
{
  public:
    using VertexSet = sl::FixedPriorityQueue<wgt_diff_type, vtx_type>::ValueSet;

    /**
    * @brief Create a new vertex queue.
    *
    * @param numVertices The number of vertices in the priority queue.
    */
    VertexQueue(
        vtx_type const numVertices) :
      m_queue(numVertices)
    {
      // do nothing
    }


    /**
    * @brief Remove an vertex from the queue.
    *
    * @param elem The vertex to remove
    */
    void remove(
        Vertex const v) noexcept
    {
      m_queue.remove(v.index);
    }


    /**
    * @brief Add an value to the queue.
    *
    * @param key The key/priority of the value to add.
    * @param value The value to add.
    */
    void add(
        wgt_type const key,
        Vertex const v) noexcept
    {
      m_queue.add(key, v.index);
    }


    /**
    * @brief Update the key associated with a given value.
    *
    * @param key The new key for the value.
    * @param value The value.
    */
    void update(
        wgt_type const key,
        Vertex const v) noexcept
    {
      m_queue.update(key, v.index);
    }


    /**
    * @brief Update the key associated with a given value by modifying the key.
    *
    * @param delta The change in priority.
    * @param v The value.
    */
    void updateByDelta(
        wgt_type const delta,
        Vertex const v) noexcept
    {
      m_queue.updateByDelta(delta, v.index);
    }

    /**
    * @brief Check if a value in present in the priority queue.
    *
    * @param value The value to check for.
    *
    * @return Whether or not the value is present.
    */
    bool contains(
        Vertex const v) const noexcept
    {
      return m_queue.contains(v.index); 
    }


    /**
    * @brief Get the key associated with the given value.
    *
    * @param value The value.
    *
    * @return The key.
    */
    wgt_type get(
        Vertex const v) const noexcept
    {
      return m_queue.get(v.index);
    }


    /**
    * @brief Pop the top value from the queue.
    *
    * @return The top value.
    */
    Vertex pop() noexcept
    {
      return Vertex::make(m_queue.pop());
    }


    /**
    * @brief Get get the top of the priority queue's value.
    *
    * @return The value.
    */
    Vertex peek() const noexcept
    {
      return Vertex::make(m_queue.peek());
    }


    /**
    * @brief Get get the top of the priority queue's value.
    *
    * @return The value.
    */
    wgt_diff_type max() const noexcept
    {
      return m_queue.max();
    }


    /**
    * @brief Get the number of vertexs in the queue.
    *
    * @return The number of vertexs.
    */
    vtx_type size() const noexcept
    {
      return static_cast<vtx_type>(m_queue.size());
    }

    /**
    * @brief Clear entries from the priority queue.
    */
    void clear() noexcept
    {
      m_queue.clear();
    }

    /**
    * @brief Get the set of vertices remainging in the queue.
    *
    * @return The remaining vertices.
    */
    VertexSet remaining() const
    {
      return m_queue.remaining();
    }

  private:
    sl::FixedPriorityQueue<wgt_diff_type, vtx_type> m_queue;
};

}

#endif
